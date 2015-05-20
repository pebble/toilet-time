//
//  DropdownMenu.swift
//  Pebble Bathroom
//
//  Created by Kevin Conley on 4/7/15.
//  Copyright (c) 2015 Kevin Conley. All rights reserved.
//

import Cocoa

class DropdownMenu: NSMenu {

    var status: String? {
        didSet {
            if status != nil {
                statusItem.title = status!
            }
        }
    }
    
    private let statusItem = NSMenuItem(title: "Connecting...", action: nil, keyEquivalent: "")
    
    func quitApp() {
        NSApplication.sharedApplication().terminate(self)
    }
    
    override init() {
        super.init()
        self.autoenablesItems = false
        
        let titleItem = NSMenuItem(title: "Pebble Bathroom", action: nil, keyEquivalent: "")
        titleItem.enabled = false
        self.addItem(titleItem)
        
        self.addItem(NSMenuItem.separatorItem())
        
        statusItem.enabled = false
        self.addItem(statusItem)
        
        self.addItem(NSMenuItem.separatorItem())
        
        let quitItem = NSMenuItem(title: "Quit", action: Selector("quitApp"), keyEquivalent: "")
        quitItem.target = self
        quitItem.enabled = true
        self.addItem(quitItem)
    }
    
    override init(title aTitle: String) {
        super.init(title: aTitle)
    }

    required init(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
}
