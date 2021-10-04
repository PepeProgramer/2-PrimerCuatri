class Parcela

  @FACTORIAL_ALQUILER_CALLE = 1.0
  @FACTORIAL_ALQUILER_CASA = 1.0
  @FACTORIAL_ALQUILER_HOTEL = 4.0

  def self.FACTORIAL_ALQUILER_CALLE
   @FACTORIAL_ALQUILER_CALLE
  end

  def self.FACTORIAL_ALQUILER_CASA
   @FACTORIAL_ALQUILER_CASA
  end

  def self.FACTORIAL_ALQUILER_HOTEL
   @FACTORIAL_ALQUILER_HOTEL
  end

  #@@FACTORIAL_ALQUILER_CALLE = 1.0

  #@@FACTORIAL_ALQUILER_CASA = 1.0

  #@@FACTORIAL_ALQUILER_HOTEL = 4.0

  def initialize(nombre, precio_compra, precio_edificar, precio_base_alquiler, max_casas)
    @nombre = nombre
    @precio_compra = precio_compra
    @precio_edificar = precio_edificar
    @precio_base_alquiler = precio_base_alquiler
    @num_casas = @num_hoteles = 0
    @max_casas = max_casas
    #@FACTORIAL_ALQUILER_CASA = @FACTORIAL_ALQUILER_CALLE = 1.0
    #@FACTORIAL_ALQUILER_HOTEL = 4.0
  end
  def nombre
    @nombre
  end

  def precioCompra
    @precio_compra
  end

  def precioEdificar
    @precio_edificar
  end

  def num_casas
    @num_casas
  end

  def num_hoteles
    @num_hoteles
  end

  def precio_alquiler_completo
    @precio_base_alquiler * (Parcela.FACTORIAL_ALQUILER_CALLE+num_casas+num_hoteles*Parcela.FACTORIAL_ALQUILER_CASA*Parcela.FACTORIAL_ALQUILER_HOTEL)
  end

  def construir_casa
    if @num_casas < @max_casas
      @num_casas +=1
    end
    true
  end

  def contruir_hotel
    @num_hoteles += 1
  end

end