package org.appspot.siprtc;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import org.webrtc.*;

import org.appspot.siprtc.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'siprtc' library on application startup.
    static {
        System.loadLibrary("siprtc");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

//        PeerConnectionFactory.initializeAndroidGlobals(getApplicationContext(), false, false, false);

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI(getApplicationContext()));
    }

    /**
     * A native method that is implemented by the 'siprtc' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI(Object context);
}