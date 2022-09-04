//source_set("libunwind") {
//-  visibility = []
//    -  if (is_fuchsia) {
//-    visibility += [ "//buildtools/third_party/libc++abi" ]
//-  } else if (is_android) {
//-    visibility += [ "//buildtools/third_party/libc++abi" ]
//-    visibility += [ "//services/tracing/public/cpp" ]
//-  }
//+#  visibility = []
//    +#  if (is_fuchsia) {
//+#    visibility += [ "//buildtools/third_party/libc++abi" ]
//+#  } else if (is_android) {
//+#    visibility += [ "//buildtools/third_party/libc++abi" ]
//+#    visibility += [ "//services/tracing/public/cpp" ]
//+#  }
//if (!is_component_build) {
//defines = [ "_LIBUNWIND_DISABLE_VISIBILITY_ANNOTATIONS" ]
//}

//dayong@dayong-ThinkPad:/mnt/data/new-webrtc/android/src/build$ git diff
//    diff --git a/config/BUILD.gn b/config/BUILD.gn
//    index 8fc6a82df..6c2686340 100644
//--- a/config/BUILD.gn
//+++ b/config/BUILD.gn
//@@ -244,6 +244,8 @@ group("common_deps") {
//
//if (use_custom_libcxx) {
//public_deps += [ "//buildtools/third_party/libc++" ]
//+  } else {
//+    public_deps += [ "//buildtools/third_party/libunwind" ]
//}
//
//if (use_afl) {


#include <jni.h>
#include <string>
#include "android/log.h"

#include <modules/utility/include/jvm_android.h>
#include <sdk/android/native_api/base/init.h>
#include <rtc_base/ssl_adapter.h>

#include "api/media_stream_interface.h"
#include "api/peer_connection_interface.h"
#include "absl/memory/memory.h"
#include "absl/types/optional.h"
#include "api/audio/audio_mixer.h"
#include "api/audio_codecs/audio_decoder_factory.h"
#include "api/audio_codecs/audio_encoder_factory.h"
#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "api/audio_codecs/builtin_audio_encoder_factory.h"
#include "api/audio_options.h"
#include "api/create_peerconnection_factory.h"
#include "api/rtp_sender_interface.h"
#include "api/video_codecs/builtin_video_decoder_factory.h"
#include "api/video_codecs/builtin_video_encoder_factory.h"
#include "api/video_codecs/video_decoder_factory.h"
#include "api/video_codecs/video_encoder_factory.h"
#include "modules/audio_device/include/audio_device.h"
#include "modules/audio_processing/include/audio_processing.h"
#include "modules/video_capture/video_capture.h"
#include "modules/video_capture/video_capture_factory.h"
#include "p2p/base/port_allocator.h"
#include "pc/video_track_source.h"
#include "rtc_base/checks.h"
#include "rtc_base/logging.h"
#include "rtc_base/rtc_certificate_generator.h"
#include "rtc_base/strings/json.h"

#include "sdk/android/src/jni/jni_helpers.h"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "TRY_WEBRTC", ##__VA_ARGS__)

std::unique_ptr<rtc::Thread> signaling_thread_;
rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection_;
rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory_;

JavaVM *g_vm = nullptr;

jint JNIEXPORT JNICALL JNI_OnLoad(JavaVM* jvm, void* reserved) {
  LOGI("JNI_OnLoad ============== enter");
  g_vm = jvm;
  webrtc::InitAndroid(jvm);
  RTC_CHECK(rtc::InitializeSSL()) << "Failed to InitializeSSL()";
  LOGI("JNI_OnLoad ============== exit");
  return JNI_VERSION_1_6;
}

struct TestFunctor {
  void operator()() {
    LOGI("TestFunctor run");
    LOGI("TestFunctor stop");
  }
};

extern "C" JNIEXPORT jstring JNICALL
Java_org_appspot_siprtc_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */, jobject context) {

  webrtc::JVM::Initialize(g_vm, context);

  auto thread = rtc::Thread::Create();
  thread->Start();
  thread->Invoke<void>(RTC_FROM_HERE, TestFunctor());
  thread->Stop();

  peer_connection_factory_ = webrtc::CreatePeerConnectionFactory(
      nullptr /* network_thread */, nullptr /* worker_thread */,
      signaling_thread_.get(), nullptr /* default_adm */,
      webrtc::CreateBuiltinAudioEncoderFactory(),
      webrtc::CreateBuiltinAudioDecoderFactory(),
      webrtc::CreateBuiltinVideoEncoderFactory(),
      webrtc::CreateBuiltinVideoDecoderFactory(), nullptr /* audio_mixer */,
      nullptr /* audio_processing */);

    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}