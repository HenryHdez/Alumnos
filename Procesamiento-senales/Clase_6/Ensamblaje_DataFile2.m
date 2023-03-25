% Simscape(TM) Multibody(TM) version: 7.5

% This is a model data file derived from a Simscape Multibody Import XML file using the smimport function.
% The data in this file sets the block parameter values in an imported Simscape Multibody model.
% For more information on this file, see the smimport function help page in the Simscape Multibody documentation.
% You can modify numerical values, but avoid any other changes to this file.
% Do not add code to this file. Do not edit the physical units shown in comments.

%%%VariableName:smiData


%============= RigidTransform =============%

%Initialize the RigidTransform structure array by filling in null values.
smiData.RigidTransform(4).translation = [0.0 0.0 0.0];
smiData.RigidTransform(4).angle = 0.0;
smiData.RigidTransform(4).axis = [0.0 0.0 0.0];
smiData.RigidTransform(4).ID = "";

%Translation Method - Cartesian
%Rotation Method - Arbitrary Axis
smiData.RigidTransform(1).translation = [9.586938 -129.24595600000001 102.550742];  % mm
smiData.RigidTransform(1).angle = 0;  % rad
smiData.RigidTransform(1).axis = [0 0 0];
smiData.RigidTransform(1).ID = "SixDofRigidTransform[Mk62tS/h+W1ug6NHc]";

%Translation Method - Cartesian
%Rotation Method - Arbitrary Axis
smiData.RigidTransform(2).translation = [-18.662153 -110.44369800000001 83.063654999999997];  % mm
smiData.RigidTransform(2).angle = 1.5707963267948968;  % rad
smiData.RigidTransform(2).axis = [0 0 1];
smiData.RigidTransform(2).ID = "SixDofRigidTransform[MC7H5yIVcr1pDYaN1]";

%Translation Method - Cartesian
%Rotation Method - Arbitrary Axis
smiData.RigidTransform(3).translation = [9.3707760000000011 67.576404000000011 143.62397099999998];  % mm
smiData.RigidTransform(3).angle = 0;  % rad
smiData.RigidTransform(3).axis = [0 0 0];
smiData.RigidTransform(3).ID = "SixDofRigidTransform[MeYLadb0CKO+1Rtg8]";

%Translation Method - Cartesian
%Rotation Method - Arbitrary Axis
smiData.RigidTransform(4).translation = [47.668258000000002 249.08049600000001 83.156860999999992];  % mm
smiData.RigidTransform(4).angle = 1.5711009132952551;  % rad
smiData.RigidTransform(4).axis = [-0.01744974930950818 -0.01744974930950818 -0.99969545987669195];
smiData.RigidTransform(4).ID = "SixDofRigidTransform[MJJniJqj50kO0g5iO]";


%============= Solid =============%
%Center of Mass (CoM) %Moments of Inertia (MoI) %Product of Inertia (PoI)

%Initialize the Solid structure array by filling in null values.
smiData.Solid(3).mass = 0.0;
smiData.Solid(3).CoM = [0.0 0.0 0.0];
smiData.Solid(3).MoI = [0.0 0.0 0.0];
smiData.Solid(3).PoI = [0.0 0.0 0.0];
smiData.Solid(3).color = [0.0 0.0 0.0];
smiData.Solid(3).opacity = 0.0;
smiData.Solid(3).ID = "";

%Inertia Type - Custom
%Visual Properties - Simple
smiData.Solid(1).mass = 0;  % kg
smiData.Solid(1).CoM = [0 0 0];  % mm
smiData.Solid(1).MoI = [0 0 0];  % kg*mm^2
smiData.Solid(1).PoI = [0 0 0];  % kg*mm^2
smiData.Solid(1).color = [1.000000000 0.000000000 0.000000000];
smiData.Solid(1).opacity = 1.000000000;
smiData.Solid(1).ID = "JHD*:*d4364895e15b4c06b64581eb";

%Inertia Type - Custom
%Visual Properties - Simple
smiData.Solid(2).mass = 0;  % kg
smiData.Solid(2).CoM = [0 0 0];  % mm
smiData.Solid(2).MoI = [0 0 0];  % kg*mm^2
smiData.Solid(2).PoI = [0 0 0];  % kg*mm^2
smiData.Solid(2).color = [1.000000000 0.756862745 0.054901961];
smiData.Solid(2).opacity = 1.000000000;
smiData.Solid(2).ID = "JHD*:*11bf37a94bc6482c2b590be7";

%Inertia Type - Custom
%Visual Properties - Simple
smiData.Solid(3).mass = 0;  % kg
smiData.Solid(3).CoM = [0 0 0];  % mm
smiData.Solid(3).MoI = [0 0 0];  % kg*mm^2
smiData.Solid(3).PoI = [0 0 0];  % kg*mm^2
smiData.Solid(3).color = [0.000000000 0.000000000 1.000000000];
smiData.Solid(3).opacity = 1.000000000;
smiData.Solid(3).ID = "JHD*:*bfd21b3c4ec36ff7830a4337";

