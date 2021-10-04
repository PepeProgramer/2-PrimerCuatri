require_relative 'parcela'

par = Parcela.new("pepe", 100, 50, 55, 3)
par.construir_casa
par.construir_casa
par.construir_casa

par.contruir_hotel
par.contruir_hotel
par.contruir_hotel

puts "El precio del alquiler es de #{par.precio_alquiler_completo}"