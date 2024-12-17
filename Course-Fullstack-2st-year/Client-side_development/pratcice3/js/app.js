// Создание похожей функции, которая отвечает за отображение и скрытие информации по нажатию ЛКМ
//Для аккордеонов
document.addEventListener("DOMContentLoaded", () => {
    // Находим все элементы заголовков аккордеона
    const titles = document.querySelectorAll(".accordion .item-title");

    titles.forEach((title) => {
        title.addEventListener("click", () => {
            // Находим следующий элемент (контент)
            const content = title.nextElementSibling;

            // Если блок уже открыт (имеет класс active) — убираем его
            if (content.classList.contains("active")) {
                content.classList.remove("active");
            } else {
                // Закрываем все другие блоки контента
                document.querySelectorAll(".accordion .item-content").forEach((item) => {
                    item.classList.remove("active");
                });
                // Открываем текущий блок
                content.classList.add("active");
            }
        });
    });
});

//Для вкладок
document.addEventListener("DOMContentLoaded", () => {
    // Находим все кнопки во вкладках
    const tabButtons = document.querySelectorAll(".tabs-header button");

    // Добавляем обработчик события клика для каждой кнопки
    tabButtons.forEach((button) => {
        button.addEventListener("click", () => {
            // Находим ID целевого блока из data-target
            const targetId = button.getAttribute("data-target");

            // Скрываем все блоки контента
            document.querySelectorAll(".tabs-body > div").forEach((tab) => {
                tab.style.display = "none";
            });

            // Показываем нужный блок контента
            const targetTab = document.querySelector(targetId);
            if (targetTab) {
                targetTab.style.display = "block";
            }
        });
    });

    // Инициализация: показываем первый таб по умолчанию
    const firstButton = tabButtons[0];
    if (firstButton) {
        firstButton.click();
    }
});
