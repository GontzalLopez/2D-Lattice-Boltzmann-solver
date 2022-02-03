# -*- coding: utf-8 -*-
"""
Created on Wed Jan 26 13:05:53 2022

@author: gontzal.lopez
"""

import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np

a=5000
b=65000
c=121
res=np.linspace(a,b,c,dtype=int);

for i in res:
    nm=str(i)        
    xfilename='Uxmag_'+nm+'.dat'
    yfilename='Uymag_'+nm+'.dat' 
    
    ux = np.loadtxt('./Ux/'+xfilename, unpack = True)
    uy = np.loadtxt('./Uy/'+yfilename, unpack = True) 
    
#    if i==a:
#        x=np.linspace(1, len(ux[:,1]), len(ux[:,1]))
#        y=np.linspace(1, len(ux[1,:]), len(ux[1,:]))
#        X, Y = np.meshgrid(x, y)
#        X=np.transpose(X)
#        Y=np.transpose(Y)
       
    obstacle=ux[:,:]==0;
    obstacle=uy[:,:]==0;
    
    ux[obstacle]=np.NaN
    uy[obstacle]=np.NaN
    
    du_dx, du_dy = np.gradient(ux)
    dv_dx, dv_dy = np.gradient(uy)
    curl = (du_dy - dv_dx)
 
                    ### curl ###    
#    plt.clf()  
#    plt.imshow(curl[:,:].transpose(), cmap=cm.bwr)
#    #plt.clim(0, 0.2)
#    cbar=plt.colorbar(orientation='horizontal');
#    cbar.set_label('Vorticity [m/s]')
#    plt.savefig('./Images/Results_'+nm+'.png',dpi=150)
    
                    ### Ux ###      
    plt.clf()  
    plt.imshow(ux[:,:].transpose(), cmap=cm.hot,vmin=-0.05,vmax=0.25)
    plt.clim(-0.06, 0.25)
    cbar=plt.colorbar(orientation='horizontal');
    cbar.set_label('Ux mag. [m/s]')
    plt.savefig('./Images/Results_'+nm+'.png',dpi=300)
            
import glob
import cv2
import os

img_array = []
for filename in sorted(glob.glob('./Images/*.png'), key=os.path.getmtime):
    img = cv2.imread(filename)
    height, width, layers = img.shape
    size = (width,height)
    img_array.append(img)
 
 
out = cv2.VideoWriter('LBM.avi',cv2.VideoWriter_fourcc(*'DIVX'), 6, size)
 
for i in range(len(img_array)):
    out.write(img_array[i])
out.release()



from PIL import Image
import glob
 
# Create the frames
frames = []
imgs = sorted(glob.glob('./Images/*.png'), key=os.path.getmtime)
for i in imgs:
    new_frame = Image.open(i)
    frames.append(new_frame)
 
# Save into a GIF file that loops forever
frames[0].save('png_to_gif.gif', format='GIF',
               append_images=frames[1:],
               save_all=True,
               duration=20, loop=0)
