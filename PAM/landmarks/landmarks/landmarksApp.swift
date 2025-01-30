//
//  landmarksApp.swift
//  landmarks
//
//  Created by Ao XIE on 28/01/2025.
//

import SwiftUI

@main
struct landmarksApp: App {
    
    @State private var modelData = ModelData()
    
    var body: some Scene {
        WindowGroup {
            ContentView()
                .environment(modelData)
        }
    }
}
