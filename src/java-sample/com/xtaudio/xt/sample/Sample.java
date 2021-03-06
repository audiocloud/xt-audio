package com.xtaudio.xt.sample;

import com.xtaudio.xt.XtException;
import com.xtaudio.xt.XtPrint;

public class Sample {

    public static void main(String[] args) throws Exception {
        int index = -1;
        if (args.length == 1) {
            index = Integer.parseInt(args[0]);
        }
        try {
            if (index == -1 || index == 0) {
                System.out.println("PrintSimple:");
                PrintSimple.main(args);
            }
            if (index == -1 || index == 1) {
                System.out.println("PrintDetailed:");
                PrintDetailed.main(args);
            }
            if (index == -1 || index == 2) {
                System.out.println("CaptureSimple:");
                CaptureSimple.main(args);
            }
            if (index == -1 || index == 3) {
                System.out.println("RenderSimple:");
                RenderSimple.main(args);
            }
            if (index == -1 || index == 4) {
                System.out.println("CaptureAdvanced:");
                CaptureAdvanced.main(args);
            }
            if (index == -1 || index == 5) {
                System.out.println("RenderAdvanced:");
                RenderAdvanced.main(args);
            }
            if (index == -1 || index == 6) {
                System.out.println("FullDuplex:");
                FullDuplex.main(args);
            }
            if (index == -1 || index == 7) {
                System.out.println("Aggregate:");
                Aggregate.main(args);
            }
        } catch (XtException e) {
            System.out.println("Error:");
            System.out.println("\tSystem: " + XtPrint.systemToString(XtException.getSystem(e.getError())));
            System.out.println("\tCause: " + XtPrint.causeToString(XtException.getCause(e.getError())));
            System.out.println("\tFault: " + XtException.getFault(e.getError()));
            System.out.println("\tText: " + XtException.getText(e.getError()));
        }
    }
}
