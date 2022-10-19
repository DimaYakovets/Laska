using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Vison.ProjectExplorer.Models;
using YamlDotNet.Serialization;
using YamlDotNet.Serialization.NamingConventions;

namespace Vison.Models
{
    internal sealed class Project
    {
        private const string ASSETS = @"\Assets";

        public string? Root { get; set; }
        public INode Assets => new FolderNode(new(Root + ASSETS));

        public string? Name { get; set; }
        public string? Version { get; set; }
        public string? Author { get; set; }
        public Dotnet? Dotnet { get; set; }
        public List<Resource>? Resources { get; set; }
        public List<Scene>? Scenes { get; set; }

        public Project()
        {

        }
        public static Project LoadFromYaml(string path)
        {
            var deserializer = new DeserializerBuilder()
                    .WithNamingConvention(PascalCaseNamingConvention.Instance)
                    .IgnoreUnmatchedProperties()
                    .Build();

            string yaml = File.ReadAllText(path);

            Project project = deserializer.Deserialize<Project>(yaml);
            project.Root = path.Substring(0, path.LastIndexOf('\\'));

            return project;
        }

    }
}
