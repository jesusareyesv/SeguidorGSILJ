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
    double P_c,I_c,D_c; int infra, distancia, dist, PWM_MIN,PWM_MAX,PWM_ABS, PWM_BASE, FRENO_CURVA, delaycurva1, delaycurva2, delay_o1, delay_o2, delay_o3, delay_o4, giro_loco;
    float tolerancia;
    
    public ArchivoEscrituraConfiguracion(String fileName, double p, double i, double d, int in, int dist,int PWM_MIN, int PWM_MAX, int PWM_ABS, int PWM_BASE, float tolerancia, int FRENO_CURVA, int delaycurva1, int delaycurva2, int delay_o1, int delay_o2, int delay_o3, int delay_o4, int giro_loco){
        super(fileName+"-config.txt");
        
        P_c = p;
        I_c = i;
        D_c = d;
        infra = in;
        distancia = dist;
        this.PWM_MIN = PWM_MIN;
        this.PWM_MAX = PWM_MAX;
        this.PWM_ABS = PWM_ABS;
        this.PWM_BASE = PWM_BASE;
        this.tolerancia = tolerancia;
        this.FRENO_CURVA = FRENO_CURVA;
        this.delaycurva1 = delaycurva1;
        this.delaycurva2 = delaycurva2;
        this.delay_o1 = delay_o1;
        this.delay_o2 = delay_o2;
        this.delay_o3 = delay_o3;
        this.delay_o4 = delay_o4;
        this.giro_loco = giro_loco;
        
        escribir();
    }
    
    @Override
    void escribir() {
        Date fecha = new Date();
        try {
            //bufferEscritura.flush();
            
            bufferEscritura.write("Archivo de configuracion. "+fecha.toString());
            bufferEscritura.newLine();
            
            bufferEscritura.write(P_c+"/k_P");bufferEscritura.newLine();
            bufferEscritura.write(I_c+"/k_I");bufferEscritura.newLine();
            bufferEscritura.write(D_c+"/k_D");bufferEscritura.newLine();
            bufferEscritura.write(infra+"/Infrarrojos");bufferEscritura.newLine();
            bufferEscritura.write(distancia+"/Distancia");bufferEscritura.newLine();
            bufferEscritura.write(PWM_MIN+"/PWM_MIN");bufferEscritura.newLine();
            bufferEscritura.write(PWM_MAX+"/PWM_MAX");bufferEscritura.newLine();
            bufferEscritura.write(PWM_ABS+"/PWM_ABS");bufferEscritura.newLine();
            bufferEscritura.write(PWM_BASE+"/PWM_BASE");bufferEscritura.newLine();
            bufferEscritura.write(tolerancia+"/tolerancia");bufferEscritura.newLine();
            bufferEscritura.write(FRENO_CURVA+"/Cantidad de veces freno curva");bufferEscritura.newLine();
            bufferEscritura.write(delaycurva1+"/delaycurva1");bufferEscritura.newLine();
            bufferEscritura.write(delaycurva2+"/delaycurva2");bufferEscritura.newLine();
            bufferEscritura.write(delay_o1+"/delay_o1");bufferEscritura.newLine();
            bufferEscritura.write(delay_o2+"/delay_o2");bufferEscritura.newLine();
            bufferEscritura.write(delay_o3+"/delay_o3");bufferEscritura.newLine();
            bufferEscritura.write(delay_o4+"/delay_o4");bufferEscritura.newLine();
            bufferEscritura.write(giro_loco+"/giro_loco_  porcentaje de giro");bufferEscritura.newLine();
            
            bufferEscritura.close();
        } catch (IOException ex) {
            Logger.getLogger(ArchivoEscrituraConfiguracion.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
}
