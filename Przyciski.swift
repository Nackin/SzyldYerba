//
//  Przyciski.swift
//  YerbaLed
//
//  Created by Bartek Wójcik on 25/06/2022.
//

import Foundation
import SwiftUI

func rainbowCycleButton() async{
    guard let url = URL(string: "http://192.168.1.54/rainbowCycle") else {
        print("Invalid URL")
        return
    }
    do {
       try await URLSession.shared.data(from: url)
// more code to come
    } catch {
    print("Invalid data")
}
}
//----------------------------------------------------------------
//----------------------------------------------------------------
func theaterChaseRainbowButton() async{
        guard let url = URL(string: "http://192.168.1.54/theaterChaseRainbow") else {
            print("Invalid URL")
            return
        }
        do {
           try await URLSession.shared.data(from: url)
    // more code to come
        } catch {
        print("Invalid data")
    }
}
//----------------------------------------------------------------
//----------------------------------------------------------------
func meteorRainButton() async{
        guard let url = URL(string: "http://192.168.1.54/meteorRain") else {
            print("Invalid URL")
            return
        }
        do {
            try await URLSession.shared.data(from: url)
        // more code to come
        } catch {
            print("Invalid data")
        }
    }
//----------------------------------------------------------------
//----------------------------------------------------------------
    func fireButton() async{
            guard let url = URL(string: "http://192.168.1.54/fire") else {
                print("Invalid URL")
                return
            }
            do {
                try await URLSession.shared.data(from: url)
            // more code to come
            } catch {
                print("Invalid data")
            }
        }
    //----------------------------------------------------------------
    //----------------------------------------------------------------
func bpmButton() async{
    guard let url = URL(string: "http://192.168.1.54/bpm") else {
        print("Invalid URL")
        return
    }
    do {
        try await URLSession.shared.data(from: url)

        // more code to come
    } catch {
        print("Invalid data")
    }
}
//----------------------------------------------------------------
//----------------------------------------------------------------
func rainbowButton() async{
        guard let url = URL(string: "http://192.168.1.54/rainbow") else {
            print("Invalid URL")
            return
        }
        do {
            try await URLSession.shared.data(from: url)
        // more code to come
        } catch {
            print("Invalid data")
        }
    }
//----------------------------------------------------------------
//----------------------------------------------------------------
func rainbowWithGlitterButton() async{
        guard let url = URL(string: "http://192.168.1.54/rainbowWithGlitter") else {
            print("Invalid URL")
            return
        }
        do {
            try await URLSession.shared.data(from: url)
        // more code to come
        } catch {
            print("Invalid data")
        }
    }
//----------------------------------------------------------------
//----------------------------------------------------------------
func confettiButton() async{
        guard let url = URL(string: "http://192.168.1.54/confetti") else {
            print("Invalid URL")
            return
        }
        do {
            try await URLSession.shared.data(from: url)
        // more code to come
        } catch {
            print("Invalid data")
        }
    }
//----------------------------------------------------------------
//----------------------------------------------------------------
func sinelonButton() async{
        guard let url = URL(string: "http://192.168.1.54/sinelon") else {
            print("Invalid URL")
            return
        }
        do {
            try await URLSession.shared.data(from: url)
        // more code to come
        } catch {
            print("Invalid data")
        }
    }
//----------------------------------------------------------------
//----------------------------------------------------------------
func juggleButton() async{
        guard let url = URL(string: "http://192.168.1.54/juggle") else {
            print("Invalid URL")
            return
        }
        do {
            try await URLSession.shared.data(from: url)
        // more code to come
        } catch {
            print("Invalid data")
        }
    }
//----------------------------------------------------------------
//----------------------------------------------------------------
func RGBLoopButton() async{
        guard let url = URL(string: "http://192.168.1.54/RGBLoop") else {
            print("Invalid URL")
            return
        }
        do {
            try await URLSession.shared.data(from: url)
        // more code to come
        } catch {
            print("Invalid data")
        }
    }
