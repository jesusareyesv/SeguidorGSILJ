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
 * @author lab
 */
public class GraficaUltrasonido extends Grafica{
    private final XYSeries lecturas = new XYSeries("Lecturas del sensor");
    private XYSeriesCollection coleccion = new XYSeriesCollection();
    
    private JFreeChart chart;
    
    public GraficaUltrasonido(ArrayList<Integer> lec){
        super("Grafica: Posicion de la linea");
        
        this.agregarLista(lec);
        
        coleccion.addSeries(lecturas);
        
        chart = ChartFactory.createXYLineChart("Lecturas Ultrasonido", "Ciclo", "Valor del sensor", coleccion, PlotOrientation.VERTICAL, true, true, false);
        
        ChartPanel panel = new ChartPanel(chart);
        
        ventanaGrafica.add(panel);
        ventanaGrafica.pack();
    }
    
    public void agregarLista(ArrayList<Integer> p){
        lecturas.clear();
        
        int inicio = 0;
        
        if(p.size() > 10000){
            inicio = p.size() - 80;
        }
        
        for (int ciclo = inicio; ciclo < p.size(); ciclo++) {
            lecturas.add(ciclo+1, p.get(ciclo));
        }
        
        contadorCiclo = p.size();
    }
    
    public void agregar(int p){
        if(contadorCiclo > 50)
            lecturas.remove(0);
        
        lecturas.add(contadorCiclo, p);
        
        contadorCiclo++;
    }
}
