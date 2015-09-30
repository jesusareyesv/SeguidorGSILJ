/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Archivos;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author lab
 */
public class ArchivoEscrituraData extends ArchivoEscritura{
    ArrayList<Double> pl,il,dl, sumapid, ew1, ew2, ea1, ea2;
    ArrayList<Integer> pwmi, pwmd,posicion,distancia,duty_time;
    
    public ArchivoEscrituraData(String fileName, ArrayList<Double> pl, ArrayList<Double> il,ArrayList<Double> dl,ArrayList<Double> sumapid,ArrayList<Double> ew1,ArrayList<Double> ew2,ArrayList<Double> ea1,ArrayList<Double> ea2, ArrayList<Integer> pwmi,ArrayList<Integer> pwmd,ArrayList<Integer> posicion, ArrayList<Integer> distancia, ArrayList<Integer> duty_time){
        super(fileName+"-data.txt");
        
        this.pl = pl;
        this.il = il;
        this.dl = dl;
        this.sumapid = sumapid;
        this.ea1 = ea1;
        this.ea2 = ea2;
        this.ew1 = ew1;
        this.ew2 = ew2;
        this.pwmd = pwmd;
        this.pwmi = pwmi;
        this.posicion = posicion;
        this.distancia = distancia;
        this.duty_time = duty_time;
        
        this.escribir();
    }
    
    public ArchivoEscrituraData(String fileName){
        super(fileName+"-data.txt");
    }
    
    @Override
     void escribir() {
        Date fecha = new Date();
        try {
            bufferEscritura.write("Archivo de Data. "+fecha.toString());
            bufferEscritura.newLine();
            
            for (int i = 0; i < pl.size(); i++) {
                bufferEscritura.write(pl.get(i)+" "+il.get(i)+" "+dl.get(i)+" "+sumapid.get(i)+" "+/*distancia.get(i)+" "*/+duty_time.get(i)+" "+pwmi.get(i)+" "+pwmd.get(i)+" "+ew1.get(i)+" "+ea1.get(i)+" "+ew2.get(i)+" "+ea2.get(i));
                bufferEscritura.newLine();
                //P I D SUMA DISTANCIA TIEMPO_CICLO PWMI PWMD EW1 EA1 EW2 EA2
            }
            
            bufferEscritura.close();
        } catch (IOException ex) {
            Logger.getLogger(ArchivoEscrituraData.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public ArrayList<Double> getPl() {
        return pl;
    }

    public void setPl(ArrayList<Double> pl) {
        this.pl = pl;
    }

    public ArrayList<Double> getIl() {
        return il;
    }

    public void setIl(ArrayList<Double> il) {
        this.il = il;
    }

    public ArrayList<Double> getDl() {
        return dl;
    }

    public void setDl(ArrayList<Double> dl) {
        this.dl = dl;
    }

    public ArrayList<Double> getSumapid() {
        return sumapid;
    }

    public void setSumapid(ArrayList<Double> sumapid) {
        this.sumapid = sumapid;
    }

    public ArrayList<Double> getEw1() {
        return ew1;
    }

    public void setEw1(ArrayList<Double> ew1) {
        this.ew1 = ew1;
    }

    public ArrayList<Double> getEw2() {
        return ew2;
    }

    public void setEw2(ArrayList<Double> ew2) {
        this.ew2 = ew2;
    }

    public ArrayList<Double> getEa1() {
        return ea1;
    }

    public void setEa1(ArrayList<Double> ea1) {
        this.ea1 = ea1;
    }

    public ArrayList<Double> getEa2() {
        return ea2;
    }

    public void setEa2(ArrayList<Double> ea2) {
        this.ea2 = ea2;
    }

    public ArrayList<Integer> getPwmi() {
        return pwmi;
    }

    public void setPwmi(ArrayList<Integer> pwmi) {
        this.pwmi = pwmi;
    }

    public ArrayList<Integer> getPwmd() {
        return pwmd;
    }

    public void setPwmd(ArrayList<Integer> pwmd) {
        this.pwmd = pwmd;
    }

    public ArrayList<Integer> getPosicion() {
        return posicion;
    }

    public void setPosicion(ArrayList<Integer> posicion) {
        this.posicion = posicion;
    }

    public ArrayList<Integer> getDistancia() {
        return distancia;
    }

    public void setDistancia(ArrayList<Integer> distancia) {
        this.distancia = distancia;
    }

    public ArrayList<Integer> getDuty_time() {
        return duty_time;
    }

    public void setDuty_time(ArrayList<Integer> duty_time) {
        this.duty_time = duty_time;
    }
    
    
}
