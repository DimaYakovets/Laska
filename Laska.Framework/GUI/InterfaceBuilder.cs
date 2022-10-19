using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laska.Framework.GUI
{
    public abstract class ControlBuilder
    {

    }

    public abstract class ContainerBuilder : ControlBuilder
    {

    }

    public sealed class BlockBuilder : ContainerBuilder
    {
        
    }

    public sealed class PageBuilder
    {
        private readonly Dictionary<string, ControlBuilder> _controls;

        public PageBuilder()
        {
            _controls = new();
        }

        public BlockBuilder AddBlock(string name, Action<BlockBuilder> action)
        {
            BlockBuilder builder = CreateWithAction(action);
            _controls.Add(name, builder);
            return builder;
        }

        private TControl CreateWithAction<TControl>(Action<TControl> action)
            where TControl : ControlBuilder, new()
        {
            TControl control = new();
            action(control);
            return control;
        }
    }

    public sealed class InterfaceBuilder
    {
        private readonly Dictionary<string, PageBuilder> _pages;
        public InterfaceBuilder()
        {
            _pages = new();
        }

        public void AddPage(string name, Action<PageBuilder> action)
        {
            PageBuilder page = new();
            action(page);
            _pages.Add(name, page);
        }
    }
}
