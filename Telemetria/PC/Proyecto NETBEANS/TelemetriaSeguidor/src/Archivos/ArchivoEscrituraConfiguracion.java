/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Archivos;

import java.io.IOException;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author lab
 */
public class ArchivoEscrituraConfiguracion extends ArchivoEscritura {
    double P_c,I_c,D_c; int infra, distancia;
    
    public ArchivoEscrituraConfiguracion(String fileName, double p, double i, double d, int in, int dist){
        super(fileName+"-config.txt");
        
        P_c = p;
        I_c = i;
        D_c = d;
        infra = in;
        distancia = dist;
        escribir();
    }
    
    @Override
    void escribir() {
        Date fecha = new Date();
        try {
            //bufferEscritura.flush();
            
            bufferEscritura.write("Archivo de configuracion. "+fecha.toString());
            bufferEscritura.newLine();
            
            bufferEscritura.write(P_c+"/P");bufferEscritura.newLine();
            bufferEscritura.write(I_c+"/I");bufferEscritura.newLine();
            bufferEscritura.write(D_c+"/D");bufferEscritura.newLine();
            bufferEscritura.write(infra+"/Infrarrojos");bufferEscritura.newLine();
            bufferEscritura.write(distancia+"/Distancia");bufferEscritura.newLine();
            
            bufferEscritura.close();
        } catch (IOException ex) {
            Logger.getLogger(ArchivoEscrituraConfiguracion.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
}
