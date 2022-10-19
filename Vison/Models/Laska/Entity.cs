using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Vison.Models.Laska
{
    [StructLayout(LayoutKind.Sequential)]
    internal unsafe struct EntityRaw
    {
        public ulong Id;
        public IntPtr Registry;
    }

    internal unsafe sealed class Entity
    {
        public EntityRaw* Ptr => _ptr;

        private readonly EntityRaw* _ptr;

        public Entity(EntityRaw* ptr)
        {
            _ptr = ptr;
        }
    }
}
