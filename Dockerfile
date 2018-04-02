FROM nikitin/boostspiritbuilder

COPY main.cpp /lab/
RUN g++ -o /lab/boostspiritlab /lab/main.cpp -lboost_system
RUN /lab/boostspiritlab
