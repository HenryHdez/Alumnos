%ONSHAPE
URL='https://cad.onshape.com/documents/e10d659a8f9e4103eb49aa50/w/15d5b228a48037828996c863/e/6b42e2cef0994c3c832af116';
Ruta='Ensamblaje';
%Crear XML
XML=smexportonshape(URL, 'FolderPath', Ruta);
%Crear ruta
Nombrearchivo=strcat(Ruta,'\',XML);
smimport(Nombrearchivo)