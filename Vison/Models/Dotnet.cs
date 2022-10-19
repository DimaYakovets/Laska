using System.Collections.Generic;

namespace Vison.Models
{
    internal sealed class Dotnet
    {
        public string? AssemblyName { get; set; }
        public string? Namespace { get; set; }
        public string? Version { get; set; }
        public List<string>? Sources { get; set; }

        public override string ToString()
        {
            return $"{AssemblyName} | {Version}";
        }
    }
}
