g++ -o fcc fcc.cpp
g++ -o equilibration equilibration.cpp
g++ -o dynamics dynamics.cpp
g++ -o RDF RDF.cpp
g++ -o correlations correlations.cpp

./fcc
./equilibration
./dynamics
./RDF
./correlations

rm fcc equilibration dynamics RDF correlations

python graphs.py