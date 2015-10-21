/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Graficas;

import java.util.ArrayList;
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
    private XYSeriesCollection coleccion = new XYSeriesCollection();
    
    private JFreeChart chart;
    
    public GraficaPosicion(ArrayList<Integer> pos){
        super("Grafica: Posicion de la linea");
        
        this.agregarLista(pos);
        
        coleccion.addSeries(posiciones);
        
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
        }
        
        contadorCiclo = p.size();
    }
    
    public void agregar(int p){
        if(contadorCiclo > 50)
            posiciones.remove(0);
        
        posiciones.add(contadorCiclo, p);
        
        contadorCiclo++;
    }
}
