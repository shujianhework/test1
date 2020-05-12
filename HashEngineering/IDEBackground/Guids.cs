// Guids.cs
// MUST match guids.h
using System;

namespace Company.IDEBackground
{
    static class GuidList
    {
        public const string guidIDEBackgroundPkgString = "f144a5be-ed19-4e58-ba2c-d9375c64ad86";
        public const string guidIDEBackgroundCmdSetString = "69452767-2529-4f4c-86fb-b8f448ac5a65";

        public static readonly Guid guidIDEBackgroundCmdSet = new Guid(guidIDEBackgroundCmdSetString);
    };
}