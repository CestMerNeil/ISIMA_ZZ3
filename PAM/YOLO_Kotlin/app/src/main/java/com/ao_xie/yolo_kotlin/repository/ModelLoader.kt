package com.ao_xie.yolo_kotlin.repository

import android.content.Context
import com.google.mlkit.common.model.LocalModel
import com.google.mlkit.vision.objects.ObjectDetection
import com.google.mlkit.vision.objects.ObjectDetector
import com.google.mlkit.vision.objects.custom.CustomObjectDetectorOptions

class ModelLoader(private val context: Context) {

    enum class ModelName(val value: String) {
        YOLO11N_FLOAT16("yolo11n_float16"),
        YOLO11N_FLOAT32("yolo11n_float32"),
        YOLO11M_FLOAT16("yolo11m_float16"),
        YOLO11M_FLOAT32("yolo11m_float32")
    }

    private val YOLO11N_FLOAT16_PATH = ModelName.YOLO11N_FLOAT16.value + ".tflite"
    private val YOLO11N_FLOAT32_PATH = ModelName.YOLO11N_FLOAT32.value + ".tflite"
    private val YOLO11M_FLOAT16_PATH = ModelName.YOLO11M_FLOAT16.value + ".tflite"
    private val YOLO11M_FLOAT32_PATH = ModelName.YOLO11M_FLOAT32.value + ".tflite"

    private fun loadYolo11nFloat16Model(): LocalModel {
        return LocalModel.Builder()
            .setAssetFilePath(YOLO11N_FLOAT16_PATH)
            .build()
    }

    private fun loadYolo11nFloat32Model(): LocalModel {
        return LocalModel.Builder()
            .setAssetFilePath(YOLO11N_FLOAT32_PATH)
            .build()
    }

    private fun loadYolo11mFloat16Model(): LocalModel {
        return LocalModel.Builder()
            .setAssetFilePath(YOLO11M_FLOAT16_PATH)
            .build()
    }

    private fun loadYolo11mFloat32Model(): LocalModel {
        return LocalModel.Builder()
            .setAssetFilePath(YOLO11M_FLOAT32_PATH)
            .build()
    }

    private fun loadModel(modelName: ModelName): LocalModel {
        return when (modelName) {
            ModelName.YOLO11N_FLOAT16 -> loadYolo11nFloat16Model()
            ModelName.YOLO11N_FLOAT32 -> loadYolo11nFloat32Model()
            ModelName.YOLO11M_FLOAT16 -> loadYolo11mFloat16Model()
            ModelName.YOLO11M_FLOAT32 -> loadYolo11mFloat32Model()
        }
    }

    fun createObjectDetector(modelName: ModelName = ModelName.YOLO11N_FLOAT16): ObjectDetector {
        val options = CustomObjectDetectorOptions.Builder(loadModel(modelName))
            .setDetectorMode(CustomObjectDetectorOptions.STREAM_MODE)
            .enableClassification()
            .enableMultipleObjects()
            .setClassificationConfidenceThreshold(0.5f)
            .setMaxPerObjectLabelCount(3)
            .build()
        return ObjectDetection.getClient(options)
    }
}

/*

    How to use this class:
    val modelLoader = ModelLoader(context)
    val objectDetector = modelLoader.createObjectDetector("yolo11n_float16")

*/