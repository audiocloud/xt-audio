using System;

namespace Xt
{
    public class Sample
    {
        [STAThread]
        public static void Main(string[] args)
        {
            int index = -1;
            if (args.Length == 1)
                index = int.Parse(args[0]);
            try
            {
                if (index == -1 || index == 0)
                {
                    Console.WriteLine("PrintSimple:");
                    PrintSimple.Main(args);
                }
                if (index == -1 || index == 1)
                {
                    Console.WriteLine("PrintDetailed:");
                    PrintDetailed.Main(args);
                }
                if (index == -1 || index == 2)
                {
                    Console.WriteLine("CaptureSimple:");
                    CaptureSimple.Main(args);
                }
                if (index == -1 || index == 3)
                {
                    Console.WriteLine("RenderSimple:");
                    RenderSimple.Main(args);
                }
                if (index == -1 || index == 4)
                {
                    Console.WriteLine("CaptureAdvanced:");
                    CaptureAdvanced.Main(args);
                }
                if (index == -1 || index == 5)
                {
                    Console.WriteLine("RenderAdvanced:");
                    RenderAdvanced.Main(args);
                }
                if (index == -1 || index == 6)
                {
                    Console.WriteLine("FullDuplex:");
                    FullDuplex.Main(args);
                }
                if (index == -1 || index == 7)
                {
                    Console.WriteLine("Aggregate:");
                    Aggregate.Main(args);
                }
            } catch (XtException e)
            {
                Console.WriteLine("Error:");
                Console.WriteLine("\tSystem: " + XtPrint.SystemToString(XtException.GetSystem(e.GetError())));
                Console.WriteLine("\tCause: " + XtPrint.CauseToString(XtException.GetCause(e.GetError())));
                Console.WriteLine("\tFault: " + XtException.GetFault(e.GetError()));
                Console.WriteLine("\tText: " + XtException.GetText(e.GetError()));
            }
        }
    }
}