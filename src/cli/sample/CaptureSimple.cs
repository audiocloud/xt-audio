using System;
using System.IO;
using System.Threading;

namespace Xt
{
    public class CaptureSimple
    {
        static readonly XtMix Mix = new XtMix(44100, XtSample.Int24);
        static readonly XtChannels Channels = new XtChannels(1, 0, 0, 0);
        static readonly XtFormat Format = new XtFormat(Mix, Channels);

        static void OnBuffer(XtStream stream, in XtBuffer buffer, object user)
        {
            var output = (FileStream)user;
            XtSafeBuffer safe = XtSafeBuffer.Get(stream);
            safe.Lock(buffer);
            var input = (byte[])safe.GetInput();
            int size = XtAudio.GetSampleAttributes(Mix.sample).size;
            if (buffer.frames > 0) output.Write(input, 0, buffer.frames * size);
            safe.Unlock(buffer);
        }

        public static void Main()
        {
            XtStreamParams streamParams;
            XtDeviceStreamParams deviceParams;

            using IDisposable audio = XtAudio.Init(null, IntPtr.Zero, null);
            XtSystem system = XtAudio.SetupToSystem(XtSetup.ConsumerAudio);
            XtService service = XtAudio.GetService(system);
            if (service == null) return;

            using XtDevice device = service.OpenDefaultDevice(false);
            if (device?.SupportsFormat(Format) != true) return;

            XtBufferSize size = device.GetBufferSize(Format);
            streamParams = new XtStreamParams(true, OnBuffer, null);
            deviceParams = new XtDeviceStreamParams(in streamParams, in Format, size.current);
            using var recording = new FileStream("xt-audio.raw", FileMode.Create, FileAccess.Write);
            using XtStream stream = device.OpenStream(in deviceParams, recording);
            using XtSafeBuffer safe = XtSafeBuffer.Register(stream, true);
            stream.Start();
            Thread.Sleep(2000);
            stream.Stop();
        }
    }
}