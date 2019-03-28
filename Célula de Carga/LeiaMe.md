# CÉLULA DE CARGA

## Strain Gauges

### 1. INTRODUÇÃO

  > O nome extensômetro significa medidor de deformação. O nome extensômetro de resistência elétrica significa medidor de deformação (mecânica) relativa através da determinação da variação da resistência elétrica. Assim, dispositivos que efetuam esta correlação são chamados de extensômetro de resistência elétrica ou strain gauges. A utilização mais conhecida e mais extensa para os Strain Gauges é na construção de células de cargas, tipicamente utilizadas na fabricação de balanças eletrônicas dos mais diversos tipos. Isto é interessante uma vez que, a célula de carga construída a partir de strain gauges, gera um sinal elétrico proporcional ao esforço mecânico incidente sobre esta. Este sinal pode ser amostrado em um display ou tela, mostrando assim a massa (esforço mecânico) incidente.<
  
 ### 2. METODOLOGIA DE MEDIÇÃO
 
   O processo de calibração de uma célula de carga consiste em submete-la a certas variações de esforços conhecidos. Ao aplicar as tensões gerará uma deformaçao que varia a resistência de extensômetro que por meio de um driver é que essas variações são possíveis de serem convertidas.
   Na calibração, foi utilizado uma célula de carga tipo Z, Figura 1, e o driver HX711, Figura 2, para realizar as medições através de um arduino. O equipamente usado para comprensão da célula de carga foi um prensa encontrada no laboratório de metais e ensaios mecânicos da Universiade Federal do Rio Grande do Norte (UFRN), em que foi solicitados 10 esforços de 0kg à 200kg e gerado uma tabela de valores gerados pela célula de carga e os da prensa.
   
   
 ##### Figura 1 - Célula de carga tipo Z
   
   
   ![](http://www.alfainstrumentos.com.br/wp-content/uploads/2016/07/Z-e-zx_pag.png)
   
   
 ###### Fonte: http://www.alfainstrumentos.com.br/produto/z-e-zx/
 
 
 ##### Figura 2 - Driver HX711 
![](http://www.electronicspro.com.pk/wp-content/uploads/2017/11/hx711-load-cell-amplifier.jpeg)
 ###### Fonte: http://www.electronicspro.com.pk/wp-content/uploads/2017/11/hx711-load-cell-amplifier.jpeg
 
### 3. Como ler dados da célula de carga tipo Z

  ### 3.1 LIGAÇÕES
  
  A célula de carga deve estar posicionada verticamente ao esforço que prende-se coletados os dados e os quatros fios devem seguir o esquemático como mostra a figura 3
  
   ##### Figura 3 - Esquemático de ligações da célula com o arduino 
  ![](https://github.com/kaikecc/PRD_ELETRONICA/blob/master/C%C3%A9lula%20de%20Carga/Imagens/ESQUEM%C3%81TICO.png)
  
   ### 3.2 CÓDIGO
   
  O código utilizado para aquisição dos dados encontra-se nesse repositório: https://bit.ly/2HWDN3E, mas para salvar os dados precisa utilizar uma extensão do Excel chamada **PLX-DAQ**: https://bit.ly/2ShGtKX a versão do excel 2013 e o tutorial de como utilizar o PLX encontra-se aqui: https://bit.ly/2HV3DoA. 
  
   ### 3.3 EXCEL
   
   Ao abrir o aplicativo do PLX abrirá no excel a seguinte janela conforme a figura 4 você deve seleciona
   
   ##### Figura 3 - Esquemático de ligações da célula com o arduino
   ![](https://github.com/kaikecc/PRD_ELETRONICA/blob/master/C%C3%A9lula%20de%20Carga/Imagens/plx.png)
   
   
  
  
  
  
  
  









