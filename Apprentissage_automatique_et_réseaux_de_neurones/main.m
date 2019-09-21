function main(input,target)
    cd('C:\Users\khadidja\Desktop\projetaarn');
    %creation d'un repertoire où on va mettre tous les resultats
    mkdir('Resultat');
    cd('Resultat');
    %creation de toutes les combinaisons possibles de notre architecture de 1 a 3 couches et de 10 a 100 couches avec un pas de 10 pour
    %chaque couche
    %0 neurons sur une couche signifie que cette couche n'existe pas ; elimination des couches redondantes ex: 10-0-10 == 10-10-0==10-10
    %architectures=table2array(setdiff(table(combvec(10:10:100,0:10:100,0:10:100)'),table(combvec(10:10:100,0,10:10:100)')));
    architectures=[5 0;5 5];
    %fonction d'erreur choisie (elle est utlisée avec les fonctions discretes)
    fonctionActivation='crossentropy';
    %nombre d'epoch maximal choisi
    max_epoch=300;
    %taux d'erreur but
    goal=0;
    %temps maximal pour un train
    max_time=300;
    %fonction d'activation choisie
    activ_hidden_layer='tansig';
    activ_output_layer='tansig';
    %fonction d'apprentissage choisie
    % fonctionApp=['trainrp ';'trainlm ';'trainoss';'trainscg';'traingdm'];
    fonctionApp=['trainrp ';'trainoss'];
    %fonction d'initialisation des poids
    %fonctionInit=['randsmall';'rands    ';'randnr   ';'randnc   '];
    fonctionInit=['randsmall'];
    %nombre d'iterations choisi
    nombre_iteration=3;
    %decoupage du dataset
    taux_app=0.70;
    taux_val=0.15;
    taux_test=0.15;
    %lancement d'apprentissage
    [~,~,valeurPerf,~]=train_architecture(fonctionActivation,max_epoch,goal,max_time,activ_hidden_layer,activ_output_layer,...
        architectures,fonctionApp,fonctionInit,nombre_iteration,input,target,taux_app,taux_val,taux_test);
    
    %sauvgarde du tableau comparatif (resultat)
    mkdir('Tableau comparatif');
    pere=cd('Tableau comparatif');
    saveTableau(valeurPerf);
    cd(pere);
end

function saveTableau(tableau)
    tableau.Properties.Description='Tableau comparatif des differentes architectures';
    writetable(tableau,'TableauComparatif.csv','Delimiter',';');
end

function [best_net,best_tr,valeurPerf]= train_network(net,n,input,target)
%refaire l'apprentissage pour le meme network(archi et paramètres) n fois
%les performances enregistrées sont
%best_time,best_acc_train,best_acc_val,best_acc_test,best_train_perf,best_val_perf,best_test_perf
[best_net,best_tr]=train(net,input,target);
for i=1:n
  mkdir (['iteration_' mat2str(i)]);
  pere=cd (['iteration_' mat2str(i)]);
  net=init(net);
  [net,tr]=train(net,input,target);
  %sauvgarde
  saveNet(net,tr,input,target);
  [best_net,best_tr]=maj_meilleur(best_net,best_tr,net,tr);
  cd(pere);
end
 %sauvegarder les resultats globaux dans un tableau
    valeurPerf=table(string(best_tr.best_perf),string(best_tr.best_vperf),string(best_tr.best_tperf),string(sum(best_tr.time)),...
      string(Accuracy(best_net,divideind(input,best_tr.trainInd),divideind(target,best_tr.trainInd))),...
      string(Accuracy(best_net,divideind(input,best_tr.valInd),divideind(target,best_tr.valInd))),...
      string(Accuracy(best_net,divideind(input,best_tr.testInd),divideind(target,best_tr.testInd))),...
      string(Accuracy(best_net,input,target)),...
      tr.stop);
  mkdir ('Meilleur');
  pere=cd ('Meilleur');
  %saugarder le meilleur pour ces parametres
  saveNet(best_net,best_tr,input,target);
  cd(pere);
end

function saveNet(net,trace,input,target)
    %sauvegarde des graphes de performances
    %matrice de confusion totale
    plotconfusion(target,net(input));
    print('Matrice_de_confusion_totale','-dpng');
    close();
    %matrice de confusion apprentissage
    plotconfusion(divideind(target,trace.trainInd),net(divideind(input,trace.trainInd)));
    print('Matrice_de_confusion_apprentissage','-dpng');
    close();
    %matrice de confusion validation
    plotconfusion(divideind(target,trace.valInd),net(divideind(input,trace.valInd)));
    print('Matrice_de_confusion_validation','-dpng');
    close();
    %matrice de confusion test
    plotconfusion(divideind(target,trace.testInd),net(divideind(input,trace.testInd)));
    print('Matrice_de_confusion_test','-dpng');
    close();
    %graphe performance
    plotperform(trace);
    print('Performance','-dpng');
    close();
    plotroc(target,net(input));
    print('ROC total','-dpng');
    close();
    plotroc(divideind(target,trace.trainInd),net(divideind(input,trace.trainInd)));
    print('ROC apprentissage','-dpng');
    close();
    plotroc(divideind(target,trace.valInd),net(divideind(input,trace.valInd)));
    print('ROC validation','-dpng');
    close();
    plotroc(divideind(target,trace.testInd),net(divideind(input,trace.testInd)));
    print('ROC test','-dpng');
    close();
    %etat apprentissage
    plottrainstate(trace);
    print('Etats Apprentissage','-dpng');
    close();
end

function saveWeight(net)
    %sauvegarde de la matrice de poids
    aux=getwb(net);
    csvwrite('matricepoids.csv',aux);
end

function acc=Accuracy(net,input,target)
    %accuracy on va prendre >0.5 subjective
                            %sinon objective
    output=net(input);
    output=output>0.5;
    acc=(sum(output==target)/size(target,2))*100;
end

function  [best_net,best_tr]=maj_meilleur(net1,tr1,net2,tr2)
%retourne le meilleur network entre deux selon notre mesure de performance
    if (est_meilleur(tr1,tr2))
        best_tr=tr1;
        best_net=net1;
    else
        best_net=net2;
        best_tr=tr2;
    end
end

function oui=est_meilleur(tr1,tr2)
    %calcule le meilleur selon la performance de : validation, test, apprentissage, temps d'execution
     if(tr1.best_vperf<tr2.best_vperf)
       oui=1;
     elseif (tr1.best_vperf>tr2.best_vperf)
         oui=0;
     elseif(tr1.best_tperf<tr2.best_tperf)
         oui=1;
     elseif(tr1.best_tperf>tr2.best_tperf)
         oui=0;
         %train
     elseif(tr1.best_perf<tr2.best_perf)
         oui=1;
     elseif(tr1.best_perf>tr2.best_perf)
         oui=0;
     else
         oui=sum(tr1.time)<sum(tr2.time);
     end
end

function [best_net,best_tr,valeurPerf,best]=train_init_Fcn(net,initFcn,n,input,target)
    %elle varie les fonctions d'initialisation
    best=0;
    %declaration du resultat
    valeurPerf=table('size',[0,10],'VariableTypes',{'string','string','string','string','string','string','string','string','string','string'});
    
    for i=1:size(initFcn,1)
        mkdir (['Fonction_Initialisation_poids_' regexprep(initFcn(i,:),'\s+','')]);
        pere=cd (['Fonction_Initialisation_poids_' regexprep(initFcn(i,:),'\s+','')]);
        %pour varier les fonctions d'initialisation pour chaque couche
        for j=1:net.numLayers
            net.layers{j}.initFcn='initwb';%une fonction d'initialisation de poids
            if(strcmp(regexprep(initFcn(i,:),'\s+',''),'randnr')||strcmp(regexprep(initFcn(i,:),'\s+',''),'randnc'))
                %les biais ne s'initialise pas par ces deux fonction d'apprentissage
                net.biases{j}.initFcn='initcon';
            else
                net.biases{j}.initFcn=regexprep(initFcn(i,:),'\s+','');
            end
        end
        for j=1:net.numLayers-1
            %initialise les poids entre le layer j vers j+1
            net.layerWeights{j+1,j}.initFcn=regexprep(initFcn(i,:),'\s+','');%feedforwardnet seul i est connecté vers i+1
        end
        %initaliser les poids de l'input (couche d'entree)
        net.inputWeights{1,1}.initFcn=regexprep(initFcn(i,:),'\s+','');
        [net,tr,val]=train_network(net,n,input,target);
        aux=table2array(val);
        %indiquer que les resultats appartiennent a cette fonction d'initialisation
        val=table(regexprep(initFcn(i,:),'\s+',''),aux(:,1),aux(:,2),aux(:,3),aux(:,4),aux(:,5),aux(:,6),aux(:,7),aux(:,8),aux(:,9));
        %ajouter ce resultat au resultat precedent
        valeurPerf=union(valeurPerf,val);
        %mettre à jour le meilleur
        if(best==0)
            best_net=net;
            best_tr=tr;
            best=1;
        elseif(est_meilleur(tr,best_tr))
            best=i;
            best_net=net;
            best_tr=tr;
        end
        cd(pere);
    end
    %sauvegarder le meilleur
    mkdir (['Meilleur ' char(valeurPerf.Var1(best))]);
    pere=cd (['Meilleur ' char(valeurPerf.Var1(best))]);
    saveNet(best_net,best_tr,input,target);
    cd(pere);
end

function [best_net,best_tr,valeurPerf,best]= train_function(net,perform_fcn,max_epoch,max_goal,max_time,trainFcs,initFcn,n,input,target)
%refaire le training n fois pour chaque fonction d'apprentissage
%retourne une matrice representante pour chaque fonction d'apprentissage, le
%meilleur network trouvé et sa trace, et retourne l'indice de la fonction
%qui a donné les meilleures performances
    %valeurPerf contient les performances de ces networks
    valeurPerf=table('size',[0,11],'VariableTypes',{'string','string','string','string','string','string','string','string','string','string','string'});
    best=0;
    for i=1:size(trainFcs,1)
        mkdir (['Fonction_apprentissage_' regexprep(trainFcs(i,:),'\s+','')]);
        pere=cd (['Fonction_apprentissage_' regexprep(trainFcs(i,:),'\s+','')]);
        net.trainFcn=regexprep(trainFcs(i,:),'\s+','');
        %initialisation des parametres
        net.performFcn = perform_fcn;
        net.trainParam.epochs=max_epoch;
        net.trainParam.goal=max_goal;
        net.trainParam.show=20;  
        net.trainParam.time=max_time;
        [net,tr,val,bestI]=train_init_Fcn(net,initFcn,n,input,target);
        aux=table2array(val);
        %indiquer que les resultats appartiennent a la fonction d'apprentissage courante
        val=table(repelem(string(regexprep(trainFcs(i,:),'\s+','')),size(initFcn,1))',aux(:,1),aux(:,2),aux(:,3),aux(:,4),aux(:,5),aux(:,6),aux(:,7),aux(:,8),aux(:,9),aux(:,10));
        %ajouter au resultat precedant
        valeurPerf=union(valeurPerf,val);
        %mettre a jour le best
        if(best==0)
            best_net=net;
            best_tr=tr;
            best=bestI;
        elseif(est_meilleur(tr,best_tr))
            best=bestI+(i-1)*size(initFcn,1);
            best_net=net;
            best_tr=tr;
        end
        cd(pere);
    end
    %sauvegarder le best
    mkdir (['Meilleur ' best_net.trainFcn ' and ' char(valeurPerf.Var2(best))]);
    pere=cd (['Meilleur ' best_net.trainFcn ' and ' char(valeurPerf.Var2(best))]);
    saveNet(best_net,best_tr,input,target);
    cd(pere);
end

function [best_net,best_tr,valeurPerf,best]=train_architecture(perform_fcn,max_epoch,max_goal,max_time,hidden_layer_act,output_layer_act,List_archi,trainFcs,initFcn,n,input,target,taux_train,taux_val,taux_test)
    %varier selon les architectures
    %initaliser le resultat
    valeurPerf=table('size',[0,12],'VariableTypes',{'string','string','string','string','string','string','string','string','string','string','string','string'});
    best=0;
    for i=1:size(List_archi,1)
        %parametre
        mkdir (['Architecture_' mat2str(nonzeros(List_archi(i,:))')]);
        pere=cd (['Architecture_' mat2str(nonzeros(List_archi(i,:))')]);
        %definir le reseau
        net=feedforwardnet(nonzeros(List_archi(i,:))');
        %configurer le reseau (creation de la couche d'entree et de sortie)
        net=configure(net,input,target);
        %les fonctions de performances
        net.plotFcns={'plotconfusion','plotperform','plotroc','plottrainstate'};
        %le decoupage de donnees
        net.divideParam.trainRatio = taux_train;
        net.divideParam.valRatio = taux_val;
        net.divideParam.testRatio = taux_test;
        %la fonction d'activation
        for j=1:size(nonzeros(List_archi(i,:))')
            net.layers{j}.transferFcn=hidden_layer_act;
        end
        net.layers{size(nonzeros(List_archi(i,:))')+1}.transferFcn=output_layer_act;
        [net,tr,val,bestI]=train_function(net,perform_fcn,max_epoch,max_goal,max_time,trainFcs,initFcn,n,input,target);
        aux=table2array(val);
        %indiquer que les resultats appartiennent à l'architecture courante
        val=table(repelem(strjoin(string(nonzeros(List_archi(i,:))')),size(initFcn,1)*size(trainFcs,1))',aux(:,1),aux(:,2),aux(:,3),aux(:,4),aux(:,5),aux(:,6),aux(:,7),aux(:,8),aux(:,9),aux(:,10),aux(:,11));
        %ajouter au resultat precedant
        valeurPerf=union(valeurPerf,val);
        %mettre a jour le best
        if(best==0)
            best_net=net;
            best_tr=tr;
            best=1;
        elseif(est_meilleur(tr,best_tr))
            best=bestI+(i-1)*size(initFcn,1)*size(trainFcs,1);
            best_net=net;
            best_tr=tr;
        end
        cd(pere);
    end
    %sauvegarder le best
    mkdir (['Meilleur ' char(valeurPerf.Var1(best)) 'and' best_net.trainFcn ' and ' initFcn(1,:)]);
    pere=cd (['Meilleur ' char(valeurPerf.Var1(best)) 'and' best_net.trainFcn ' and ' initFcn(1,:)]);
    saveNet(best_net,best_tr,input,target);
    saveWeight(net);
    %intituler le tableau resultant
    valeurPerf.Properties.VariableNames={'Architecture','Fonction_apprentissage','Fonction_initialisation_des_poids',...
        'Performance_apprentissage','Performance_de_validation','Performance_de_test','Temps_execution',...
        'Exactitude_apprentissage','Exactitude_de_validation','Exactitude_de_test','Exactitude_totale','Condition_Arret_active'};
    cd(pere);
end
