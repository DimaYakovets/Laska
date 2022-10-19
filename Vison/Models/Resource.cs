using System.Collections.Generic;

namespace Vison.Models
{
    internal sealed class Resource
    {
        public long Id { get; set; }
        public string? Type { get; set; }
        public string? Path { get; set; }
        public Dictionary<string, object>? Properties { get; set; }

        public override string ToString()
        {
            return $"{Id} : {Type} | {Path}";
        }
    }
}
