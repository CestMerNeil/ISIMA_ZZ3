package com.ao_xie.yolo_kotlin.ui.components

import androidx.compose.foundation.layout.*
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.CameraAlt
import androidx.compose.material.icons.filled.Cameraswitch
import androidx.compose.material.icons.filled.PhotoLibrary
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp

@Composable
fun BottomBar(
    onModelChange: (String) -> Unit,
    onCaptureClick: () -> Unit,
    onGalleryClick: () -> Unit,
    onSwitchCameraClick: () -> Unit
) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .padding(8.dp),
        horizontalArrangement = Arrangement.SpaceBetween,
        verticalAlignment = Alignment.CenterVertically
    ) {
        // 模型选择器
        DropdownMenu(
            expanded = true, // 示例展开状态
            onDismissRequest = { /* TODO: 关闭逻辑 */ }
        ) {
            listOf("YOLO11N", "YOLO11M").forEach { model ->
                DropdownMenuItem(onClick = { onModelChange(model) }) {
                    Text(text = model)
                }
            }
        }

        // 拍摄按钮
        IconButton(onClick = onCaptureClick) {
            Icon(Icons.Default.CameraAlt, contentDescription = "Capture")
        }

        // 相册按钮
        IconButton(onClick = onGalleryClick) {
            Icon(Icons.Default.PhotoLibrary, contentDescription = "Open Gallery")
        }

        // 翻转摄像头按钮
        IconButton(onClick = onSwitchCameraClick) {
            Icon(Icons.Default.Cameraswitch, contentDescription = "Switch Camera")
        }
    }
}