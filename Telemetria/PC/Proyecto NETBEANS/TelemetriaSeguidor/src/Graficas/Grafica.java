/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Graficas;

import java.awt.GridLayout;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;

/**
 *
 * @author jesus
 */
public abstract class Grafica {
    protected JFrame ventanaGrafica;
    protected int contadorCiclo = 0;
    private static Date date;
    protected String fecha;

    public static final int nMuestrasEnPantalla = 100;


    public Grafica(String name){
        ventanaGrafica = new JFrame(name);
        ventanaGrafica.setLayout(new GridLayout(0,1));
        //ventanaGrafica.setVisible(true);
        ventanaGrafica.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        date = new Date();
        fecha = date.toLocaleString();
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

    public void guardarGraficaComoPNG(JFreeChart chart,String name){
        (new Thread() {
            public void run() {
                try {
                    ChartUtilities.saveChartAsPNG(new File("DataCollection/graficasGuardadas/"+name+"("+fecha+").png"), chart, 800, 600);
                } catch (IOException ex) {
                    //JOptionPane.showMessageDialog(null, "Grafica shit", "Oh!", JOptionPane.ERROR_MESSAGE);
                }
                System.out.println("Hilo");
            }
        }).start();

    }
}
