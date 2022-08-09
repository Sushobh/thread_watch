package com.example.myapplication

import android.os.Build
import android.os.Bundle
import android.os.Debug
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.example.myapplication.databinding.ActivityMainBinding
import java.io.File
import java.lang.reflect.Method
import java.nio.file.Files
import java.nio.file.Paths


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    private var mPackageCodePath = ""

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        try {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                mPackageCodePath = getPackageCodePath()
                val classLoader: ClassLoader = getClassLoader()
                val findLibrary: Method =
                    ClassLoader::class.java.getDeclaredMethod("findLibrary", String::class.java)
                val jvmtiAgentLibPath = findLibrary.invoke(classLoader, "myapplication")
                val filesDir: File = getFilesDir()
                val jvmtiLibDir = File(filesDir, "jvmti")
                if (!jvmtiLibDir.exists()) {
                    jvmtiLibDir.mkdirs()
                }
                val agentLibSo = File(jvmtiLibDir, "agent.so")
                if (agentLibSo.exists()) {
                    agentLibSo.delete()
                }
                Files.copy(
                    Paths.get(File(jvmtiAgentLibPath.toString()).getAbsolutePath()),
                    Paths.get(agentLibSo.getAbsolutePath())
                )
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
                    Debug.attachJvmtiAgent(agentLibSo.getAbsolutePath(), null, classLoader)
                } else {
                    try {
                        val vmDebugClazz = Class.forName("dalvik.system.VMDebug")
                        val attachAgentMethod: Method =
                            vmDebugClazz.getMethod("attachAgent", String::class.java)
                        attachAgentMethod.setAccessible(true)
                        attachAgentMethod.invoke(null, agentLibSo.getAbsolutePath())
                    } catch (ex: Exception) {
                        ex.printStackTrace()
                    }
                }
                System.loadLibrary("myapplication")
            }
        } catch (ex: Exception) {
            ex.printStackTrace()
        }

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = "测试文案"
        binding.sampleText.setOnClickListener {
            Thread({
                Log.e("iehshx-jni","测试线程")
            }).apply {
                name = "iehshx"
            }.start()
        }
    }


    companion object {
        // Used to load the 'myapplication' library on application startup.
        init {
//            System.loadLibrary("myapplication")
        }
    }
}