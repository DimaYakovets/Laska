using System.Linq.Expressions;
using System.Reflection;
using System.Reflection.Emit;

namespace Laska.Dotnet;

internal readonly struct ScriptInfo
{
    private struct MethodRequirements
    {
        public Type ReturnType { get; init; }
        public Type[] Parameters { get; init; }
    }

    public readonly Type ScriptType;

    public readonly Action<object> Init;
    public readonly Action<object, float> EarlyUpdate;
    public readonly Action<object, float> FixedUpdate;
    public readonly Action<object, float> Update;
    public readonly Action<object, float> LateUpdate;
    public readonly Action<object> Delete;

    public ScriptInfo(Type type)
    {
        ScriptType = type;

        Init = TryCreateScriptCallback(ScriptType, nameof(Init));
        EarlyUpdate = TryCreateScriptCallback<float>(ScriptType, nameof(EarlyUpdate));
        FixedUpdate = TryCreateScriptCallback<float>(ScriptType, nameof(FixedUpdate));
        Update = TryCreateScriptCallback<float>(ScriptType, nameof(Update));
        LateUpdate = TryCreateScriptCallback<float>(ScriptType, nameof(LateUpdate));
        Delete = TryCreateScriptCallback(ScriptType, nameof(Delete));

        CreateFields(type);
    }

    private void CreateFields(Type type)
    {
        const BindingFlags flags = BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public;

        foreach (var field in type.GetFields(flags))
        {
            Console.WriteLine("field: {0} {1}", field.FieldType.Name, field.Name);

            if (field.FieldType == typeof(float))
            {
                CreateGetter<float>(type, field);
            }
        }
    }

    private static Action<object> TryCreateScriptCallback(Type type, string name)
    {
        MethodInfo method = GetInstanceMethodInfo(type, name, new MethodRequirements()
        {
            Parameters = Type.EmptyTypes,
            ReturnType = typeof(void)
        });

        if (method == null)
        {
            return null!;
        }

        return CreateActionIL(type, method);
    }
    private static Action<object, Arg0> TryCreateScriptCallback<Arg0>(Type type, string name)
    {
        MethodInfo method = GetInstanceMethodInfo(type, name, new MethodRequirements()
        {
            Parameters = new Type[] { typeof(Arg0) },
            ReturnType = typeof(void)
        });

        if (method == null)
        {
            return null!;
        }

        return CreateActionIL<Arg0>(type, method);
    }

    private static Action<object> CreateAction(Type instanceType, MethodInfo method)
    {
        const bool tailCall = true;

        ParameterExpression paramaterInstance = Expression.Parameter(typeof(object), "instance");
        UnaryExpression castToInstaneType = Expression.Convert(paramaterInstance, instanceType);
        MethodCallExpression methodCall = Expression.Call(castToInstaneType, method);

        return Expression.Lambda<Action<object>>(methodCall, tailCall, paramaterInstance).Compile();
    }
    private static Action<object, Arg0> CreateAction<Arg0>(Type instanceType, MethodInfo method)
    {
        const bool tailCall = true;

        ParameterExpression paramaterInstance = Expression.Parameter(typeof(object), "instance");
        ParameterExpression paramaterArg0 = Expression.Parameter(typeof(Arg0), "arg0");
        UnaryExpression castToInstaneType = Expression.Convert(paramaterInstance, instanceType);
        MethodCallExpression methodCall = Expression.Call(castToInstaneType, method, paramaterArg0);

        return Expression.Lambda<Action<object, Arg0>>(methodCall, tailCall, paramaterInstance, paramaterArg0).Compile();
    }

    private static Action<object> CreateActionIL(Type instanceType, MethodInfo method)
    {
        DynamicMethod dynamicMethod = new(string.Empty, typeof(void), new[]
        {
            typeof(object)
        });

        ILGenerator il = dynamicMethod.GetILGenerator();

        il.Emit(OpCodes.Ldarg_0);
        il.Emit(OpCodes.Castclass, instanceType);
        il.Emit(OpCodes.Call, method);
        il.Emit(OpCodes.Ret);

        return dynamicMethod.CreateDelegate<Action<object>>();
    }
    private static Action<object, Arg0> CreateActionIL<Arg0>(Type instanceType, MethodInfo method)
    {
        DynamicMethod dynamicMethod = new(string.Empty, typeof(void), new[]
        {
            typeof(object),
            typeof(Arg0)
        });

        ILGenerator il = dynamicMethod.GetILGenerator();
        il.Emit(OpCodes.Ldarg_1);
        il.Emit(OpCodes.Ldarg_0);
        il.Emit(OpCodes.Castclass, instanceType);
        il.Emit(OpCodes.Call, method);
        il.Emit(OpCodes.Ret);

        return dynamicMethod.CreateDelegate<Action<object, Arg0>>();
    }

    private static Action<object, TValue> CreateSetter<TValue>(Type instanceType, FieldInfo field)
    {
        ParameterExpression parameterInstance = Expression.Parameter(typeof(object), "instance");
        ParameterExpression parameterValue = Expression.Parameter(typeof(TValue), "value");

        UnaryExpression castToInstanceType = Expression.Convert(parameterInstance, instanceType);
        MemberExpression fieldAccess = Expression.Field(castToInstanceType, field);
        BinaryExpression assign = Expression.Assign(fieldAccess, parameterValue);

        return Expression.Lambda<Action<object, TValue>>(assign).Compile();
    }
    private static Func<object, TValue> CreateGetter<TValue>(Type instanceType, FieldInfo field)
    {
        DynamicMethod dynamicMethod = new(string.Empty, typeof(TValue), new[]
        {
            typeof(object)
        });

        ILGenerator il = dynamicMethod.GetILGenerator();
        il.Emit(OpCodes.Ldarg_0);
        il.Emit(OpCodes.Castclass, instanceType);
        il.Emit(OpCodes.Ldflda, field);
        il.Emit(OpCodes.Ret);

        return dynamicMethod.CreateDelegate<Func<object, TValue>>();
    }

    private static FieldInfo GetInstanceFieldInfo(Type type, string name)
    {
        const BindingFlags bindingFlags = BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public;

        return type.GetField(name, bindingFlags)!;
    }
    private static MethodInfo GetInstanceMethodInfo(Type type, string name, MethodRequirements reqs)
    {
        const BindingFlags bindingFlags = BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public;

        MethodInfo method = type.GetMethod(name, bindingFlags)!;
        ParameterInfo[] args;

        if (method == null)
        {
            return null!;
        }

        if (method.ReturnType != reqs.ReturnType)
        {
            return null!;
        }

        args = method.GetParameters();

        if (args.Length != reqs.Parameters.Length)
        {
            return null!;
        }

        for (int i = 0; i < args.Length; i++)
        {
            if (reqs.Parameters[args[i].Position] != args[i].ParameterType)
            {
                return null!;
            }
        }

        return method;
    }

    public override string ToString()
    {
        return $"{ScriptType.Namespace}::{ScriptType.Name} | {ScriptType.Assembly.FullName}";
    }
}
