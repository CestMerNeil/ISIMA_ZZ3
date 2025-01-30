//
//  ContentView.swift
//  landmarks
//
//  Created by Ao XIE on 28/01/2025.
//

import SwiftUI


struct ContentView: View {
    var body: some View {
        LandmarkList()
    }
}


#Preview {
    ContentView()
        .environment(ModelData())
}
