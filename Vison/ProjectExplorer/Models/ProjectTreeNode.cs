using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vison.ProjectExplorer.Models
{
    enum NodeType
    {
        None,

        Project,
        Folder,
        Scene,
        Image,

        CSharp
    }
    internal abstract class FSNode : INode
    {
        public NodeType Type { get; set; }
        public abstract bool IsFolder { get; }
        public abstract string Title { get; }
        public abstract IEnumerable<INode> Children { get; }
        public string Icon
        {
            get
            {
                if (IsFolder)
                {
                    return "Icons/ProjectTree/folder_icon.png";
                }
                else
                {
                    return Type switch
                    {
                        _ => "Icons/ProjectTree/file_empty_icon.png",
                    };
                }
            }
        }
    }

    internal sealed class FileNode : FSNode
    {
        public override bool IsFolder => false;
        public override string Title => _file.Name;
        public override IEnumerable<INode> Children => Enumerable.Empty<INode>();

        private readonly FileInfo _file;

        public FileNode(FileInfo file)
        {
            _file = file;
        }
    }

    internal sealed class FolderNode : FSNode
    {
        public override bool IsFolder => true;
        public override string Title => _dir.Name;
        public override IEnumerable<INode> Children => 
            _dir.GetDirectories().Select(f => new FolderNode(f) as INode)
            .Concat(_dir.GetFiles().Select(f => new FileNode(f)));

        private readonly DirectoryInfo _dir;

        public FolderNode(DirectoryInfo dir)
        {
            _dir = dir;
        }
    }
}
