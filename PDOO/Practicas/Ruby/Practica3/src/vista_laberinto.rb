require_relative 'Controlador_laberinto/Estado_juego'
class Vista_laberinto

  def initialize(controlador)
    @controlador = controlador
  end
  def informe_dentro(habitacion, vidas)
    puts "Habitación: #{habitacion}     vidas: #{vidas}"
  end

  def informe_final(vidas)
    puts "Vidas: #{vidas}"
  end

  def menu_usuario
    salir = false
    while !salir do
      estado = @controlador.estado_juego
      #estado = 0
      case estado
      when Controlador_laberinto::Estado_juego::EN_ENTRADA_LABERINTO
        vidas = -1
        puts "Num vidas: "
        while vidas <= 0 || vidas > 10 do
          vidas = gets.chomp.to_i #no se me detiene para escribir el dato
        end
        @controlador.entrar(vidas)
        #puts "vidas: #{vidas}"
      when Controlador_laberinto::Estado_juego::DENTRO_VIVO
        informe_dentro(@controlador.habitacion_usuario, @controlador.vidas)
        # puts "Pulsa una tecla para continuar: "
        # gets.chomp
        direccion = @controlador.intentar_avanzar()
        puts "Dirección a la que se avanza: #{Modelo_laberinto::Lista_direcciones[direccion]}"
      when Controlador_laberinto::Estado_juego::DENTRO_MUERTO
        informe_final(@controlador.vidas)
        salir = true
      when Controlador_laberinto::Estado_juego::EN_SALIDA_LABERINTO
        informe_final(@controlador.vidas)
        salir = true
      end
    end
  end
end