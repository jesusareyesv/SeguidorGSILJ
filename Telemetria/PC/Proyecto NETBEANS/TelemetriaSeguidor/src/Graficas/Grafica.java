/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Graficas;

import java.awt.GridLayout;
import javax.swing.JFrame;

/**
 *
 * @author jesus
 */
public abstract class Grafica {
    protected JFrame ventanaGrafica;
    protected int contadorCiclo = 0;
    
    public Grafica(String name){
        ventanaGrafica = new JFrame(name);
        ventanaGrafica.setLayout(new GridLayout(0,1));
        ventanaGrafica.setVisible(true);
        ventanaGrafica.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
    }
        
    public void mostrarGrafica(){
        if(ventanaGrafica.isVisible())
            ventanaGrafica.setVisible(false);
        else
            ventanaGrafica.setVisible(true);    
    }
    
    public boolean getVisibilidad() {
        return ventanaGrafica.isVisible();
    }
}
