#Python script to obtain the graphs

from plots import *
from ROOT import *

PLOT = lambda x,y: plot( range(len(x)),x,y )

rdf     = readdata('RDF.dat')
Rc,Vc   = readdata('Correlations.dat')
t,E,K,V = readdata('EKV.dat')

print rdf
plots = [rdf,Rc,Vc,E,K,V]
names = ['rdf.pdf','Rc.pdf','Vc.pdf','E.pdf','K.pdf','V.pdf']
map( PLOT, plots, names )
plot(t,[E,K,V],'Energies.pdf')