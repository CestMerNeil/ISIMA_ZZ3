package com.ao_xie.yolo_kotlin.ui.components

import androidx.compose.foundation.layout.*
import androidx.compose.material.*
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import androidx.compose.ui.viewinterop.AndroidView
import androidx.camera.view.PreviewView

@Composable
fun CameraPreview(
    detectedObjects: List<String>, // 检测到的目标
    modifier: Modifier = Modifier
) {
    Box(modifier = modifier.fillMaxSize()) {
        // 相机预览层
        AndroidView(
            modifier = Modifier.fillMaxSize(),
            factory = { context ->
                PreviewView(context).apply {
                    // CameraX 的预览初始化可以放在这里
                }
            }
        )

        // 检测结果叠加层
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(16.dp),
            verticalArrangement = Arrangement.Top
        ) {
            detectedObjects.forEach { obj ->
                Text(
                    text = obj,
                    color = Color.Red,
                    style = MaterialTheme.typography.body2
                )
            }
        }
    }
}