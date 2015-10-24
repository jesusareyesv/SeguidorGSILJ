/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Graficas;

import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

/**
 *
 * @author jesus
 */
public class GraficaPosicion extends Grafica {
    private final XYSeries posiciones = new XYSeries("Valores de la posición");
    private final XYSeries centro = new XYSeries("Centro");
    private XYSeriesCollection coleccion = new XYSeriesCollection();
    
    private JFreeChart chart;
    
    public GraficaPosicion(ArrayList<Integer> pos){
        super("Grafica: Posicion de la linea");
        
        this.agregarLista(pos);
        
        coleccion.addSeries(posiciones);
        coleccion.addSeries(centro);
        
        chart = ChartFactory.createXYLineChart("Posicion de la linea", "Ciclo", "Valor de la libreria", coleccion, PlotOrientation.HORIZONTAL, true, true, false);
        
        ChartPanel panel = new ChartPanel(chart);
        
        ventanaGrafica.add(panel);
        ventanaGrafica.pack();
    }
    
    public void agregarLista(ArrayList<Integer> p){
        posiciones.clear();
        
        int inicio = 0;
        
        if(p.size() > 10000){
            inicio = p.size() - 80;
        }
        
        for (int ciclo = inicio; ciclo < p.size(); ciclo++) {
            posiciones.add(ciclo+1, p.get(ciclo));
            centro.add(ciclo+1,2500);
        }
        
        contadorCiclo = p.size();
    }
    
    public void agregar(int p){
        if(contadorCiclo > 0 && contadorCiclo % nMuestrasEnPantalla == 0){
            try {
                this.guardarGraficaComoPNG((JFreeChart)chart.clone(), "Posicion/Posicion-grafica"+contadorCiclo/nMuestrasEnPantalla);
            } catch (CloneNotSupportedException ex) {
                JOptionPane.showMessageDialog(null, "Error al copiar charts");
            }
        }
        
        if(contadorCiclo > nMuestrasEnPantalla){
            posiciones.remove(0);
            centro.remove(0);
        }
        
        posiciones.add(contadorCiclo, p);
        centro.add(contadorCiclo,2500);
        
        contadorCiclo++;
    }
}
