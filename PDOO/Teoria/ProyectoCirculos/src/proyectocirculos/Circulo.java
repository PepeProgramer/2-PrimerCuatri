/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package proyectocirculos;

/**
 *
 * @author jordi
 */
public class Circulo {

    //Atributos y métodos de clase
    private static int NUM_CIRCULOS = 0;

    public static int cuantosCirculoshay() {
        return NUM_CIRCULOS;
    }

    //Atributos y metodos de instancia
    private float radio;
    private float x, y;
    private String color;
    private Circulo concentrico;

    public Circulo(float radio, float x, float y) {
        //this.radio = radio;
        setRadio(radio);
        this.x = x;
        this.y = y;
        this.concentrico = null;
        NUM_CIRCULOS++;
    }

    public Circulo() {
        this(1, 0, 0);
        /*setRadio(1);
        this.x = 0;
        this.y = 0;
        NUM_CIRCULOS++;
        this.concentrico = null;*/
    }

    public void pintar() {
        System.out.println("El círculo tiene radio: " + radio + " y centro: "
                + x + "," + y);
    }

    public float getRadio() {
        return radio;
    }

    public float getX() {
        return x;
    }

    public float getY() {
        return y;
    }

    public String getColor() {
        return color;
    }

    public void setRadio(float radio) {
        if (radio > 0) {
            this.radio = radio;
        } else {
            this.radio = 1;
        }
    }

    public Punto evaluar(float angulo) {
        double rad = (2 * Math.PI * angulo) / 360;
        double x = this.x + (Math.cos(rad) * this.radio);
        double y = this.y + (Math.sin(rad) * this.radio);
        return new Punto(x, y);
    }

    public void addConcentrico(Circulo c) {
        this.concentrico = c;
        c.concentrico = this;
    }

    public float grosor() {
        float gr;
        if (this.concentrico != null) {
            gr = Math.abs(this.radio - this.concentrico.getRadio());
        } else {
            gr = this.radio;
        }
        return gr;
    }
    
    public double area(){
        return this.radio*this.radio*Math.PI;
    }

}
