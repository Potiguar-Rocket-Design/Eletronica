# CÉLULA DE CARGA

## Strain Gauges

### 1. INTRODUÇÃO

  > O nome extensômetro significa medidor de deformação. O nome extensômetro de resistência elétrica significa medidor de deformação (mecânica) relativa através da determinação da variação da resistência elétrica. Assim, dispositivos que efetuam esta correlação são chamados de extensômetro de resistência elétrica ou strain gauges. A utilização mais conhecida e mais extensa para os Strain Gauges é na construção de células de cargas, tipicamente utilizadas na fabricação de balanças eletrônicas dos mais diversos tipos. Isto é interessante uma vez que, a célula de carga construída a partir de strain gauges, gera um sinal elétrico proporcional ao esforço mecânico incidente sobre esta. Este sinal pode ser amostrado em um display ou tela, mostrando assim a massa (esforço mecânico) incidente.<
  
 ### 2. METODOLOGIA DE MEDIÇÃO
 
   Utilizando a célula de carga tipo Z, Figura 1, com faixa nominal de medição de 1T e com driver HX711 foi possível realizar as medições através do arduino. A coleta dos dados foram feitas por uma prensa encontrada no laboratório de metais e ensaios mecânicos da Universiade Federal do Rio Grande do Norte (UFRN), onde foi posicionado a célula de carga no modo de compressão da prensa e realizada a calibração de 0 a 200kg.
   
 ##### Figura 1 - Célula de carga tipo Z
   
   
   ![](http://www.alfainstrumentos.com.br/wp-content/uploads/2016/07/Z-e-zx_pag.png)
   
   
 ###### Fonte: http://www.alfainstrumentos.com.br/produto/z-e-zx/
 
 
 ##### Figura 2 - Driver HX711
 
![](http://www.electronicspro.com.pk/wp-content/uploads/2017/11/hx711-load-cell-amplifier.jpeg)

 ###### Fonte: http://www.electronicspro.com.pk/wp-content/uploads/2017/11/hx711-load-cell-amplifier.jpeg
 

  O código utilizado para aquisição dos dados encontra-se nesse repositório: https://bit.ly/2HWDN3E, mas para salvar os dados precisa utilizar uma extensão do Excel chamada **PLX-DAQ**: https://bit.ly/2ShGtKX a versão do excel utilizado foi 2013 e o tutorial de como utilizar o PLX encontra-se aqui: https://bit.ly/2HV3DoA. 









