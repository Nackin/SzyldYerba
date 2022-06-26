//
//  ContentView.swift
//  YerbaLed
//
//  Created by Bartek Wójcik on 17/06/2022.
//

import SwiftUI

struct ContentView: View {
    @State var current = "RainbowCycle"
    var body: some View {
        VStack{
            Spacer()
            HStack{
                Spacer()
                Text("Obecne ustawienie: ")
                    .font(.title2)
                Spacer()
                Text(current).frame(width: 200, height: 50, alignment: .center).background(Color.cyan)
                    .foregroundColor(Color.black)
                 .cornerRadius(15)
                Spacer()
            }.padding()
            Text("Dostępne opcje:")
                .font(.title2)
            HStack{
                Spacer()
                Button(action: {
                    Task{
                    await rainbowCycleButton()  //do action
                    }
                    self.current = "RainbowCycle"
                }) {
                    Label("RainbowCycle", systemImage: "1.circle")
                        .frame(width: 160 , height: 50, alignment: .center)
                }.background(Color.cyan)
                    .foregroundColor(Color.black)
                 .cornerRadius(15)
                Spacer()
                Button(action: {
                    Task {
                        await theaterChaseRainbowButton()//do action
                        
                    }
                    self.current = "TheaterChaseRainbow"
                }) {
                    Label("TheaterChaseRainbow", systemImage: "2.circle")
                        .frame(width: 220 , height: 50, alignment: .center)
                        
                }.background(Color.cyan)
                    .foregroundColor(Color.black)
                    .cornerRadius(15)
                
                Spacer()
            }
            HStack{
                Spacer()
                Button(action: {
                    Task {
                        await meteorRainButton()//do action
                        
                    }
                    self.current = "MeteorRain"
                       
                }) {
                    Label("MeteorRain", systemImage: "cloud.rain")
                        .frame(width: 160 , height: 50, alignment: .center)
                        
                }.background(Color.cyan)
                    .foregroundColor(Color.black)
                 .cornerRadius(15)
                Spacer()
                Button(action: {
                    Task{
                        await fireButton()//do action
                        
                    }
                    self.current = "Fire"
                }) {
                    Label("Fire", systemImage: "flame")
                        .frame(width: 90 , height: 50, alignment: .center)
                        
                }.background(Color.cyan)
                    .foregroundColor(Color.black)
                    .cornerRadius(15)
                
                Spacer()
                Button(action: {
                    Task{
                        await rainbowButton()
                        
                    }//do action
                    self.current = "Rainbow"
                }) {
                    Label("Rainbow", systemImage: "3.circle")
                        .frame(width: 110 , height: 50, alignment: .center)
                        
                }.background(Color.cyan)
                    .foregroundColor(Color.black)
                    .cornerRadius(15)
                
                Spacer()
            }
            HStack{
                Spacer()
                Button(action: {
                    Task{
                        await rainbowWithGlitterButton()
                        
                    }
                    self.current = "RainbowWithGlitter"//do action
                }) {
                    Label("RainbowWithGlitter", systemImage: "4.circle")
                        .frame(width: 200 , height: 50, alignment: .center)
                        
                }.background(Color.cyan)
                    .foregroundColor(Color.black)
                 .cornerRadius(15)
                Spacer()
                Button(action: {
                    Task{
                        await confettiButton()
                        
                    }
                    self.current = "Confetti"
                       //do action
                }) {
                    Label("Confetti", systemImage: "5.circle")
                        .frame(width: 120 , height: 50, alignment: .center)
                        
                }.background(Color.cyan)
                    .foregroundColor(Color.black)
                    .cornerRadius(15)
                
                Spacer()
            }
            HStack{
                Spacer()
                Button(action: {
                    Task{
                        await sinelonButton()
                        
                    }
                    self.current = "Sinelon"
                       //do action
                }) {
                    Label("Sinelon", systemImage: "6.circle")
                        .frame(width: 120 , height: 50, alignment: .center)
                        
                }.background(Color.cyan)
                    .foregroundColor(Color.black)
                 .cornerRadius(15)
                Spacer()
                Button(action: {
                    Task{
                        await juggleButton()
                        
                    }
                    self.current = "Juggle"
                       //do action
                }) {
                    Label("Juggle", systemImage: "7.circle")
                        .frame(width: 120 , height: 50, alignment: .center)
                        
                }.background(Color.cyan)
                    .foregroundColor(Color.black)
                    .cornerRadius(15)
                
                Spacer()
                Button(action: {
                    Task{
                        await bpmButton()  //do action
                        self.current = "BPM"
                    }
                }) {
                    Label("BPM", systemImage: "timer")
                        .frame(width: 120 , height: 50, alignment: .center)
                        
                }.background(Color.cyan)
                    .foregroundColor(Color.black)
                    .cornerRadius(15)
                
                Spacer()
            }
            HStack{
                Spacer()
                Button(action: {
                    Task{
                        await RGBLoopButton()
                        
                    }
                    self.current = "RGBLoop"
                       //do action
                }) {
                    Label("RGBCycle", systemImage: "timer")
                        .frame(width: 150 , height: 50, alignment: .center)
                        
                }.background(Color.cyan)
                    .foregroundColor(Color.black)
                    .cornerRadius(15)
                
                Spacer()
            }

            Spacer()
            HStack{
                Spacer()
                Text("                                     ") //Zrobienie odpowiedniego odstępu
                Spacer()
                
                Image("logo2")
                Spacer()
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
            .preferredColorScheme(.light)
            
    }
}
