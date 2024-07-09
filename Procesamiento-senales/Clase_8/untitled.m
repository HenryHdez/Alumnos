function varargout = miGUI(varargin)
% MI_GUI MATLAB code for miGUI.fig
%      MI_GUI, by itself, creates a new MI_GUI or raises the existing
%      singleton*.
%
%      H = MI_GUI returns the handle to a new MI_GUI or the handle to
%      the existing singleton*.
%
%      MI_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MI_GUI.M with the given input arguments.
%
%      MI_GUI('Property','Value',...) creates a new MI_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before miGUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to miGUI_OpeningFcn via varargin.
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help miGUI

% Last Modified by GUIDE v2.5 27-May-2024 14:00:00

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @miGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @miGUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT

% --- Executes just before miGUI is made visible.
function miGUI_OpeningFcn(hObject, eventdata, handles, varargin)
% Choose default command line output for miGUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes miGUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% --- Outputs from this function are returned to the command line.
function varargout = miGUI_OutputFcn(hObject, eventdata, handles) 
% Get default command line output from handles structure
varargout{1} = handles.output;

% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% Crear el objeto de análisis de espectro
specAnalyzer = dsp.SpectrumAnalyzer('SampleRate', 1e3);

% Definir la señal de transmisión
txWaveform = randn(1000, 1); % Ejemplo de señal aleatoria

% Definir señales de recepción para 4 usuarios
rxWaveform_user1 = randn(1000, 1);
rxWaveform_user2 = randn(1000, 1);
rxWaveform_user3 = randn(1000, 1);
rxWaveform_user4 = randn(1000, 1);

% Definir potencias para cada usuario
power_user1 = 10; % Ejemplo de potencia
power_user2 = 15;
power_user3 = 20;
power_user4 = 25;

% Combinar señales de recepción ponderadas por las raíces cuadradas de sus potencias
combined_rxWaveform = rxWaveform_user1 .* sqrt(power_user1) + ...
                      rxWaveform_user2 .* sqrt(power_user2) + ...
                      rxWaveform_user3 .* sqrt(power_user3) + ...
                      rxWaveform_user4 .* sqrt(power_user4);

% Configurar el objeto de análisis de espectro para usar el objeto axes de la GUI
specAnalyzer.SpectrumType = 'Power';
specAnalyzer.PlotAsTwoSidedSpectrum = false;

% Ejecutar la función 'step' con los parámetros especificados
step(specAnalyzer, txWaveform, ...
     [rxWaveform_user1, rxWaveform_user2, rxWaveform_user3, rxWaveform_user4], ...
     combined_rxWaveform);

% Capturar la gráfica generada por el objeto de análisis de espectro y mostrarla en el objeto axes de la GUI
axes(handles.axes1); % Hacer que el objeto axes1 sea el objeto actual
plot(specAnalyzer); % Dibujar la gráfica en el objeto axes1

% --- Executes during object creation, after setting all properties.
function axes1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate axes1

