// MINIMOS QUADRADOS - REGRESSÃO LINEAR

clc
clear all;
arq = uigetfile();

m = fscanfMat(arq);

//X = input("DIGITE A MATRZ X: ");
//c = input("DIGITE O VETOR SOLUCAO: ");

// X = [1,2;1,3.5;1,6.5]
// c = [1.2;3.7;4.5]
a = length(m(:,1))
X = [m(:,1) ones(a, 1)]
c = m(:,2);

function [E , e] = mqrl(X,c)
    
    
    
    XT = X'; // TRANSPORTA DE X
    XTX = XT*X; // MULTIPLICACA O DA MATRIX TRANSPORTA * X;
    XTC = XT*c;
    
    
    //PROCESSO DE ESCALONAMENTO
    I = inv(XTX);    
    E = I*XTC;
    //*************************
    
    e = X*E - c;
    e = sqrt(sum(abs(e.^2)))
        
   
   
endfunction

[E e] = mqrl(X,c) // PARA MOSTRA O RESULTADO





//CALIBRACAO 1: E  =  [-0.0002264 1877.7218] , ERRO: 12.044758
// CALIBRACAO 2: E  = [-0.0002253  1868.6669] , ERRO: 16.104674
// CALIBRACAO 3: E  = [-0.0002253  1868.9719] , ERRO: 14.457288


