using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vison.ProjectExplorer.Models
{
    interface INode
    {
        public string Title { get; }
        public string Icon { get; }
        public IEnumerable<INode> Children { get; }
    }
}
