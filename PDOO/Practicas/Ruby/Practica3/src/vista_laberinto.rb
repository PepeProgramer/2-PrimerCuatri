class Vista_laberinto

  def initialize(controlador)
    @controlador = controlador
  end

  def menu_usuario
    estado = @controlador.estado()

    case estado
    when Controlador_laberinto::EN_ENTRADA_LABERINTO
      vidas = -1
      while vidas <= 0 || vidas > 10 do
        vidas = gets.chomp #no se me detiene para escribir el dato
      end
      @controlador.entrar(vidas)
    when Controlador_laberinto::DENTRO_VIVO
      informe_dentro(@controlador.habitacion_usuario(), @controlador.vidas())
      puts "Pulsa una tecla para continuar: "
      tecla = gets.chomp
      puts @controlador.intentar_avanzar()

    when Controlador_laberinto::DENTRO_MUERTO
      informe_final(@controlador.vidas())
    when Controlador_laberinto::DENTRO_MUERTO
      informe_final(@controlador.vidas())
    end
  end

  def informe_dentro(habitacion, vidas)
    puts "Habitación: #{habitacion}     vidas: #{vidas}"
  end

  def informe_final(vidas)
    puts "Vidas: #{vidas}"
  end

end