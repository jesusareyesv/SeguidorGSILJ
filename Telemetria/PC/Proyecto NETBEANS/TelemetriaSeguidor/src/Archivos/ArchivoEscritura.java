/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Archivos;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;

/**
 *
 * @author lab
 */
public abstract class ArchivoEscritura {
    protected BufferedWriter bufferEscritura;
    
    public ArchivoEscritura(){}
    
    public ArchivoEscritura(String fileName){
        changeFile(fileName);
    }
    
    abstract void escribir();
    
    public void changeFile(String fileName){
        try {
            bufferEscritura = new BufferedWriter(new FileWriter("DataCollection/data_texto/"+fileName));
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(null, "No se pudo abrir el archivo.", "ERROR", JOptionPane.ERROR_MESSAGE);
        }
    }
}
