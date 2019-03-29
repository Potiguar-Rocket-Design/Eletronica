# CÉLULA DE CARGA

## Strain Gauges

### 1. INTRODUÇÃO

  > O nome extensômetro significa medidor de deformação. O nome extensômetro de resistência elétrica significa medidor de deformação (mecânica) relativa através da determinação da variação da resistência elétrica. Assim, dispositivos que efetuam esta correlação são chamados de extensômetro de resistência elétrica ou strain gauges. A utilização mais conhecida e mais extensa para os Strain Gauges é na construção de células de cargas, tipicamente utilizadas na fabricação de balanças eletrônicas dos mais diversos tipos. Isto é interessante uma vez que, a célula de carga construída a partir de strain gauges, gera um sinal elétrico proporcional ao esforço mecânico incidente sobre esta. Este sinal pode ser amostrado em um display ou tela, mostrando assim a massa (esforço mecânico) incidente.
  
 ### 2. METODOLOGIA DE MEDIÇÃO
 
   O processo de calibração de uma célula de carga consiste em submete-la a certas variações de esforços conhecidos. Ao aplicar as tensões gerará uma deformaçao que varia a resistência de um extensômetro que por meio de um driver é que essas variações são possíveis de serem convertidas.
   Na calibração, foi utilizado uma célula de carga tipo Z, Figura 1, e o driver HX711, Figura 2, para realizar as medições através de um arduino. O equipamente usado para comprensão da célula de carga foi um prensa encontrada no laboratório de metais e ensaios mecânicos da Universiade Federal do Rio Grande do Norte (UFRN), em que foi solicitados 10 esforços de 0kg à 200kg e gerado uma tabela de valores gerados pela célula de carga e os da prensa.
   
   
 ##### Figura 1 - Célula de carga tipo Z
   
   
   ![](http://www.alfainstrumentos.com.br/wp-content/uploads/2016/07/Z-e-zx_pag.png)
   
   
 ###### Fonte: http://www.alfainstrumentos.com.br/produto/z-e-zx/
 
 
 ##### Figura 2 - Driver HX711 
 
![](http://www.electronicspro.com.pk/wp-content/uploads/2017/11/hx711-load-cell-amplifier.jpeg)

 ###### Fonte: http://www.electronicspro.com.pk/wp-content/uploads/2017/11/hx711-load-cell-amplifier.jpeg
 
 
   Foram feitas três calibrações e os dados foram processados utilizando o Scilab que nele foi desenvolvido um algoritmo de regresão linear que se encontra nesse repositório https://bit.ly/2FzfBS0 a figura 3 mostra o gráfico da regressão. O resultado da regressão gerou três  funções de conversão dos valores e a que teve o menor erro quadrático foi a escolhida. A função está abaixo :
   
     F(x) = (-0.0002264 * x) + 1877.7218
     
  F(x) --> Resulta nos peso em kg;
  
  x    --> Os valores da célula obtido pelo arduino
  
  ##### Figura 3 - Resultados da regressão linear da calibração
   
 ![](https://github.com/kaikecc/PRD_ELETRONICA/blob/master/C%C3%A9lula%20de%20Carga/Imagens/regressão%20lineaar%20dos%20valores.png)
   
   
 
### 3. Como ler dados da célula de carga tipo Z

  #### 3.1 LIGAÇÕES
  
  A célula de carga deve estar posicionada verticamente ao esforço que prende-se coletar os dados e os quatros fios devem seguir o esquemático como mostra a figura 4.
  
   ##### Figura 4 - Esquemático de ligações da célula com o arduino 
   
  ![](https://github.com/kaikecc/PRD_ELETRONICA/blob/master/C%C3%A9lula%20de%20Carga/Imagens/ESQUEM%C3%81TICO.png)
  
   
   
   #### 3.2 CÓDIGO
   
  O código utilizado para aquisição dos dados encontra-se nesse repositório: https://bit.ly/2HWDN3E, mas para salvar os dados precisa utilizar uma extensão do Excel chamada **PLX-DAQ**: https://bit.ly/2ShGtKX a versão do excel 2013. O o tutorial de como utilizar o PLX encontra-se aqui: https://bit.ly/2HV3DoA. E para um melhor entendimento código você pode assistir esse do WR Kits: https://bit.ly/2OwPsHz.
  
   #### 3.3 EXCEL
   
   Ao abrir o aplicativo do PLX no excel a seguinte janela conforme a figura 5 é aberta, você deve seleciona a porta COM em que o arduino está conectado no computador e depois selecionar a velocidade de transmissão (baund) que pode ser configurado no programa do enviado para o arduino. 
   
   ##### Figura 5 - Esquemático de ligações da célula com o arduino
   ![](https://github.com/kaikecc/PRD_ELETRONICA/blob/master/C%C3%A9lula%20de%20Carga/Imagens/plx.png)
   
  
  
  
  
  
  
  
  









