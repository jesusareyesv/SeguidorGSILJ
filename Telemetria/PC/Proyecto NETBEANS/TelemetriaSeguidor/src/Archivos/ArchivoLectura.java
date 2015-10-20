/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Archivos;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import javax.swing.JOptionPane;

/**
 *
 * @author lab
 */
public abstract class ArchivoLectura {
    static BufferedReader bufferEscritura;
    
    public ArchivoLectura(){}
    
    public ArchivoLectura(String fileName){
        changeFile(fileName);
    }
    
    abstract void leer();
    
    void changeFile(String fileName){
        try {
            bufferEscritura = new BufferedReader(new FileReader(fileName));
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(null, "No se pudo abrir el archivo.", "ERROR", JOptionPane.ERROR_MESSAGE);
        }
    }
}
