//
//  AppDelegate.swift
//  Pebble Bathroom
//
//  Created by Kevin Conley on 4/6/15.
//  Copyright (c) 2015 Kevin Conley. All rights reserved.
//

import Cocoa

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {

    let bathroomUpdateInterval = 3.0 // in seconds

    let menu = DropdownMenu()
    let statusItem = NSStatusBar.systemStatusBar().statusItemWithLength(-1)

    func setBathroomOccupied() {
        if let statusButton = self.statusItem.button {
            statusButton.image = NSImage(named: "bathroom-occupied")
        }
        menu.status = "Occupied"
    }
    
    func setBathroomVacant() {
        if let statusButton = self.statusItem.button {
            statusButton.image = NSImage(named: "bathroom-vacant")
        }
        menu.status = "Vacant"
    }
    
    func setBathroomUnknown() {
        if let statusButton = self.statusItem.button {
            statusButton.image = NSImage(named: "bathroom-unknown")
        }
    }
    
    func scheduleNextUpdate() {
        // Schedule a timer to update the bathroom state
        let timer = NSTimer(timeInterval: bathroomUpdateInterval, target: self, selector: Selector("updateBathroomState"), userInfo: nil, repeats: false)
        NSRunLoop.mainRunLoop().addTimer(timer, forMode: NSDefaultRunLoopMode)
    }
    
    func updateBathroomState() {
        println("Timer fired.")
        
        let bathroomUrl = "http://10.0.126.68"
        let url = NSURL(string: bathroomUrl)
        // Set the timeout interval for the request to 4 seconds
        let urlRequest = NSURLRequest(URL: url!, cachePolicy: NSURLRequestCachePolicy.UseProtocolCachePolicy, timeoutInterval: 4.0)
        let session = NSURLSession.sharedSession()
        let task = session.dataTaskWithRequest(urlRequest, completionHandler: {data, response, error -> Void in
            if (error != nil) {
                println("Network Error: \(error.localizedDescription)")
                
                self.scheduleNextUpdate()
                self.menu.status = "Connection error. Retrying..."
                self.setBathroomUnknown()

                return
            }
            
            var err: NSError?
            var jsonResult = NSJSONSerialization.JSONObjectWithData(data, options: NSJSONReadingOptions.MutableContainers, error: &err) as NSDictionary
            if (err != nil) {
                println("JSON Error: \(err!.localizedDescription)")
                
                self.scheduleNextUpdate()
                self.menu.status = "JSON parsing error. Retrying..."
                self.setBathroomUnknown()
                
                return
            }
            if let bathroomIsLocked = jsonResult["locked"] as? Bool {
                dispatch_async(dispatch_get_main_queue(), {
                    if bathroomIsLocked {
                        self.setBathroomOccupied()
                    } else {
                        self.setBathroomVacant()
                    }
                })
                self.scheduleNextUpdate()
            }
        })
        
        task.resume()
    }
    
    func applicationDidFinishLaunching(aNotification: NSNotification) {
        statusItem.menu = menu
        
        // Initially we don't know the bathroom state
        setBathroomUnknown()
        
        // Start by immediately trying to get the bathroom state
        updateBathroomState()
    }
}
