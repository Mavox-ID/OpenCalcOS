#!/bin/bash

# Собираем список всех файлов
files=($(find . -type f -not -path '*/.git/*'))
total=${#files[@]}
batch_size=10
count=0

echo "Всего файлов: $total. Начинаю коммитить пачками по $batch_size..."

for ((i=0; i<$total; i+=batch_size)); do
    # Берем срез из 10 файлов
    chunk=("${files[@]:$i:$batch_size}")
    
    # Добавляем их в индекс
    git add "${chunk[@]}"
    
    # Делаем коммит
    git commit -m "Batch commit: files $i to $((i + ${#chunk[@]}))" --no-verify
    
    # Прогресс
    ((count+=batch_size))
    percent=$((count * 100 / total))
    printf "\rПрогресс: %d%% (%d/%d)" $percent $count $total
done

echo -e "\nГотово! Все файлы закоммичены локально."
echo "Делаю финальный push (это может занять время)..."
git push -u origin main
