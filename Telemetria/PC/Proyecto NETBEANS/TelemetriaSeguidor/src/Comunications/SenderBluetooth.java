/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Comunications;

import java.io.IOException;
import java.io.OutputStream;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author jesus.reyes
 */
public class SenderBluetooth {
    private OutputStream output =null;
    
    
    public SenderBluetooth(OutputStream out){
        this.output = out;
    }
    
    public boolean writeData(String out){
        boolean correct = false;
        
        try{
            output.write(out.getBytes());
            correct = true;
        }catch(IOException e){
            System.err.println("Error al escribir desde el archivo");
        }
        
        return correct;
    }
    
    public boolean disconnect(){
        try {
            output.close();
            return true;
        } catch (IOException ex) {
            System.err.println("Problema al cerrar el flujo de salida.");
            return false;
        }
    }
    
}
