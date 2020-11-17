package xt.sample;

import xt.audio.CoreEnums.XtSetup;
import xt.audio.CoreEnums.XtSystem;
import xt.audio.CoreStructs.XtMix;
import xt.audio.CoreStructs.XtVersion;
import xt.audio.XtAudio;
import xt.audio.XtDevice;
import xt.audio.XtException;
import xt.audio.XtService;
import java.util.Optional;

public class PrintDetailed {

    static void onError(String location, String message) {
        System.out.println(location + ": " + message);
    }

    public static void main() throws Exception {
        try(AutoCloseable audio = XtAudio.init("Sample", null, PrintDetailed::onError)) {
            XtVersion version = XtAudio.getVersion();
            System.out.println("Version: " + version.major + "." + version.minor);
            XtSystem pro = XtAudio.setupToSystem(XtSetup.PRO_AUDIO);
            System.out.println("Pro Audio: " + pro + " (" + (XtAudio.getService(pro) != null) + ")");
            XtSystem system = XtAudio.setupToSystem(XtSetup.SYSTEM_AUDIO);
            System.out.println("System Audio: " + system + " (" + (XtAudio.getService(system) != null) + ")");
            XtSystem consumer = XtAudio.setupToSystem(XtSetup.CONSUMER_AUDIO);
            System.out.println("Consumer Audio: " + consumer + " (" + (XtAudio.getService(consumer) != null) + ")");

            for(XtSystem s: XtAudio.getSystems()) {
                XtService service = XtAudio.getService(s);
                System.out.println("System " + s + ":");
                System.out.println("  Device count: " + service.getDeviceCount());
                System.out.println("  Capabilities: " + service.getCapabilities());
                try(XtDevice defaultInput = service.openDefaultDevice(false)) {
                    System.out.println("  Default input: " + defaultInput);
                }
                try(XtDevice defaultOutput = service.openDefaultDevice(true)) {
                    System.out.println("  Default output: " + defaultOutput);
                }

                for(int d = 0; d < service.getDeviceCount(); d++)
                    try(XtDevice device = service.openDevice(d)) {
                        Optional<XtMix> mix = device.getMix();
                        System.out.println("  Device " + device + ":");
                        System.out.println("    Input channels: " + device.getChannelCount(false));
                        System.out.println("    Output channels: " + device.getChannelCount(true));
                        System.out.println("    Interleaved access: " + device.supportsAccess(true));
                        System.out.println("    Non-interleaved access: " + device.supportsAccess(false));
                        if(mix.isPresent())
                            System.out.println("    Current mix: " + mix.get().rate + " " + mix.get().sample);
                    }
            }
        } catch(XtException e) {
            System.out.println(XtAudio.getErrorInfo(e.getError()));
        }
    }
}