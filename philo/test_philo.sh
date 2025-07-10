#!/bin/bash

# ============================================
#     TEST DEFINITIVO PARA PHILOSOPHERS
# ============================================

# Colores
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Contadores
PASS=0
FAIL=0

# Función para imprimir headers
print_header() {
    echo -e "\n${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
}

# Verificar que existe el ejecutable
if [ ! -f "./philo" ]; then
    echo -e "${RED}Error: No se encuentra ./philo${NC}"
    echo "Compila primero con: make"
    exit 1
fi

# ============================================
#              TESTS BÁSICOS
# ============================================

print_header "🔍 TESTS DE ARGUMENTOS INVÁLIDOS"

echo -e "\n[TEST] Sin argumentos"
./philo 2>&1 | grep -q "philo" && echo -e "${GREEN}✅ PASS${NC}: Muestra uso correcto" || { echo -e "${RED}❌ FAIL${NC}: No muestra mensaje de error"; ((FAIL++)); }
((PASS++))

echo -e "\n[TEST] Número negativo de filósofos"
./philo -5 800 200 200 2>&1 | grep -q -i "error\|negativ" && echo -e "${GREEN}✅ PASS${NC}: Rechaza números negativos" || { echo -e "${RED}❌ FAIL${NC}: Acepta números negativos"; ((FAIL++)); }
((PASS++))

echo -e "\n[TEST] Más de 200 filósofos"
./philo 201 800 200 200 2>&1 | grep -q -i "200\|max" && echo -e "${GREEN}✅ PASS${NC}: Rechaza más de 200 filósofos" || { echo -e "${RED}❌ FAIL${NC}: Acepta más de 200 filósofos"; ((FAIL++)); }
((PASS++))

echo -e "\n[TEST] Letras en vez de números"
./philo 5 abc 200 200 2>&1 | grep -q -i "error\|digit" && echo -e "${GREEN}✅ PASS${NC}: Rechaza letras" || { echo -e "${RED}❌ FAIL${NC}: No valida correctamente"; ((FAIL++)); }
((PASS++))

# ============================================
#          TESTS QUE NO DEBEN MORIR
# ============================================

print_header "✅ TESTS SIN MUERTES ESPERADAS"

echo -e "\n${YELLOW}[TEST 1]${NC} ./philo 5 800 200 200"
echo "Esperando 5 segundos..."
timeout 5 ./philo 5 800 200 200 > test1.log 2>&1
if [ $? -eq 124 ]; then
    echo -e "${GREEN}✅ PASS${NC}: Corrió 5 segundos sin muertes"
    ((PASS++))
else
    echo -e "${RED}❌ FAIL${NC}: Hubo una muerte inesperada"
    tail -n 5 test1.log
    ((FAIL++))
fi
rm -f test1.log

echo -e "\n${YELLOW}[TEST 2]${NC} ./philo 4 410 200 200"
echo "Esperando 5 segundos..."
timeout 5 ./philo 4 410 200 200 > test2.log 2>&1
if [ $? -eq 124 ]; then
    echo -e "${GREEN}✅ PASS${NC}: Corrió 5 segundos sin muertes"
    ((PASS++))
else
    echo -e "${RED}❌ FAIL${NC}: Hubo una muerte inesperada"
    tail -n 5 test2.log
    ((FAIL++))
fi
rm -f test2.log

echo -e "\n${YELLOW}[TEST 3]${NC} ./philo 5 800 200 200 7"
echo "Todos deben comer 7 veces y terminar..."
./philo 5 800 200 200 7 > test3.log 2>&1
if ! grep -q "died" test3.log; then
    MEALS=$(grep -c "is eating" test3.log)
    if [ $MEALS -eq 35 ]; then  # 5 filósofos * 7 comidas
        echo -e "${GREEN}✅ PASS${NC}: Todos comieron 7 veces sin muertes"
        ((PASS++))
    else
        echo -e "${RED}❌ FAIL${NC}: Número incorrecto de comidas: $MEALS (esperado: 35)"
        ((FAIL++))
    fi
else
    echo -e "${RED}❌ FAIL${NC}: Alguien murió cuando no debía"
    grep "died" test3.log
    ((FAIL++))
fi
rm -f test3.log

echo -e "\n${YELLOW}[TEST 4]${NC} ./philo 2 420 200 200"
echo "Los 2 filósofos deben alternarse perfectamente..."
timeout 3 ./philo 2 420 200 200 > test4.log 2>&1
if [ $? -eq 124 ] && ! grep -q "died" test4.log; then
    echo -e "${GREEN}✅ PASS${NC}: Alternancia perfecta sin muertes"
    ((PASS++))
else
    echo -e "${RED}❌ FAIL${NC}: Problema con la alternancia"
    tail -n 5 test4.log
    ((FAIL++))
fi
rm -f test4.log

# ============================================
#          TESTS QUE DEBEN MORIR
# ============================================

print_header "💀 TESTS CON MUERTES ESPERADAS"

echo -e "\n${YELLOW}[TEST 5]${NC} ./philo 1 200 200 200"
echo "El único filósofo debe morir..."
timeout 1 ./philo 1 200 200 200 > test5.log 2>&1
if grep -q "died" test5.log; then
    DEATH_TIME=$(grep "died" test5.log | awk '{print $1}')
    if [ "$DEATH_TIME" -ge 200 ] && [ "$DEATH_TIME" -le 210 ]; then
        echo -e "${GREEN}✅ PASS${NC}: Murió en el momento correcto ($DEATH_TIME ms)"
        ((PASS++))
    else
        echo -e "${RED}❌ FAIL${NC}: Murió en momento incorrecto: $DEATH_TIME ms"
        ((FAIL++))
    fi
else
    echo -e "${RED}❌ FAIL${NC}: El filósofo no murió"
    ((FAIL++))
fi
rm -f test5.log

echo -e "\n${YELLOW}[TEST 6]${NC} ./philo 4 310 200 100"
echo "Al menos un filósofo debe morir..."
timeout 2 ./philo 4 310 200 100 > test6.log 2>&1
if grep -q "died" test6.log; then
    echo -e "${GREEN}✅ PASS${NC}: Un filósofo murió como esperado"
    grep "died" test6.log
    ((PASS++))
else
    echo -e "${RED}❌ FAIL${NC}: Nadie murió cuando debía"
    ((FAIL++))
fi
rm -f test6.log

# ============================================
#         TESTS DE SINCRONIZACIÓN
# ============================================

print_header "⏱️  TESTS DE PRECISIÓN TEMPORAL"

echo -e "\n${YELLOW}[TEST 7]${NC} Verificando precisión de muerte"
echo "Un filósofo debe morir exactamente a los 200ms (±10ms)..."
./philo 1 200 200 200 > test7.log 2>&1
DEATH_TIME=$(grep "died" test7.log | awk '{print $1}')
if [ -n "$DEATH_TIME" ]; then
    if [ "$DEATH_TIME" -ge 200 ] && [ "$DEATH_TIME" -le 210 ]; then
        echo -e "${GREEN}✅ PASS${NC}: Muerte precisa a los $DEATH_TIME ms"
        ((PASS++))
    else
        echo -e "${RED}❌ FAIL${NC}: Muerte imprecisa: $DEATH_TIME ms (esperado: 200-210ms)"
        ((FAIL++))
    fi
else
    echo -e "${RED}❌ FAIL${NC}: No se detectó muerte"
    ((FAIL++))
fi
rm -f test7.log

# ============================================
#           TESTS DE RENDIMIENTO
# ============================================

print_header "🚀 TESTS DE RENDIMIENTO"

echo -e "\n${YELLOW}[TEST 8]${NC} ./philo 200 800 200 200"
echo "Probando con máximo de filósofos (200)..."
timeout 3 ./philo 200 800 200 200 > test8.log 2>&1
if [ $? -eq 124 ]; then
    echo -e "${GREEN}✅ PASS${NC}: Maneja 200 filósofos correctamente"
    ((PASS++))
else
    echo -e "${RED}❌ FAIL${NC}: Falla con 200 filósofos"
    ((FAIL++))
fi
rm -f test8.log

echo -e "\n${YELLOW}[TEST 9]${NC} Verificando CPU usage"
echo "El programa no debe usar 100% CPU (busy waiting)..."
timeout 2 ./philo 4 410 200 200 > /dev/null 2>&1 &
PHILO_PID=$!
sleep 0.5
CPU_USAGE=$(ps -p $PHILO_PID -o %cpu | tail -n 1 | tr -d ' ')
kill $PHILO_PID 2>/dev/null
wait $PHILO_PID 2>/dev/null

if (( $(echo "$CPU_USAGE < 50" | bc -l) )); then
    echo -e "${GREEN}✅ PASS${NC}: CPU usage aceptable ($CPU_USAGE%)"
    ((PASS++))
else
    echo -e "${RED}❌ FAIL${NC}: CPU usage muy alto ($CPU_USAGE%) - posible busy waiting"
    ((FAIL++))
fi

# ============================================
#           TESTS DE MEMORIA
# ============================================

print_header "🔍 TESTS DE MEMORIA"

echo -e "\n${YELLOW}[TEST 10]${NC} Verificando memory leaks"
echo "Ejecutando con valgrind..."

# Verificar si valgrind está instalado
if command -v valgrind &> /dev/null; then
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
             --error-exitcode=1 ./philo 4 410 200 200 5 > valgrind.log 2>&1
    
    if [ $? -eq 0 ] || [ $? -eq 124 ]; then
        if grep -q "no leaks are possible" valgrind.log || grep -q "0 bytes in 0 blocks" valgrind.log; then
            echo -e "${GREEN}✅ PASS${NC}: Sin memory leaks"
            ((PASS++))
        else
            echo -e "${RED}❌ FAIL${NC}: Memory leaks detectados"
            grep "definitely lost\|indirectly lost" valgrind.log
            ((FAIL++))
        fi
    else
        echo -e "${RED}❌ FAIL${NC}: Errores detectados por valgrind"
        grep "ERROR SUMMARY" valgrind.log
        ((FAIL++))
    fi
    rm -f valgrind.log
else
    echo -e "${YELLOW}⚠️  SKIP${NC}: valgrind no instalado"
fi

# ============================================
#          TESTS DE DATA RACES
# ============================================

print_header "🔒 TESTS DE CONCURRENCIA"

echo -e "\n${YELLOW}[TEST 11]${NC} Verificando data races con helgrind"

if command -v valgrind &> /dev/null; then
    timeout 3 valgrind --tool=helgrind --error-exitcode=1 ./philo 4 410 200 200 3 > helgrind.log 2>&1
    
    if ! grep -q "data race" helgrind.log && ! grep -q "Possible data race" helgrind.log; then
        echo -e "${GREEN}✅ PASS${NC}: Sin data races detectados"
        ((PASS++))
    else
        echo -e "${RED}❌ FAIL${NC}: Posibles data races detectados"
        grep -A 5 "data race" helgrind.log | head -n 10
        ((FAIL++))
    fi
    rm -f helgrind.log
else
    echo -e "${YELLOW}⚠️  SKIP${NC}: valgrind no instalado"
fi

# ============================================
#         TESTS DE CASOS EXTREMOS
# ============================================

print_header "💥 TESTS DE CASOS EXTREMOS"

echo -e "\n${YELLOW}[TEST 12]${NC} ./philo 2 60 60 60"
echo "Valores mínimos extremos..."
timeout 1 ./philo 2 60 60 60 > test12.log 2>&1
DEATHS=$(grep -c "died" test12.log)
if [ $DEATHS -ge 1 ]; then
    echo -e "${GREEN}✅ PASS${NC}: Maneja valores extremos correctamente"
    ((PASS++))
else
    echo -e "${YELLOW}⚠️  WARNING${NC}: Nadie murió con valores extremos"
fi
rm -f test12.log

echo -e "\n${YELLOW}[TEST 13]${NC} ./philo 5 800 200 200 2147483647"
echo "Probando con INT_MAX comidas..."
timeout 2 ./philo 5 800 200 200 2147483647 > test13.log 2>&1
if [ $? -eq 124 ] && ! grep -q "died" test13.log; then
    echo -e "${GREEN}✅ PASS${NC}: Maneja INT_MAX correctamente"
    ((PASS++))
else
    echo -e "${RED}❌ FAIL${NC}: Problema con INT_MAX"
    ((FAIL++))
fi
rm -f test13.log

# ============================================
#              RESUMEN FINAL
# ============================================

print_header "📊 RESUMEN DE RESULTADOS"

TOTAL=$((PASS + FAIL))
PERCENTAGE=$((PASS * 100 / TOTAL))

echo -e "\nTests pasados: ${GREEN}$PASS${NC}"
echo -e "Tests fallidos: ${RED}$FAIL${NC}"
echo -e "Total: $TOTAL"
echo -e "Porcentaje: ${PERCENTAGE}%"

if [ $FAIL -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ¡TODOS LOS TESTS PASARON! 🎉${NC}"
    exit 0
else
    echo -e "\n${RED}❌ Algunos tests fallaron. Revisa tu código.${NC}"
    exit 1
fi