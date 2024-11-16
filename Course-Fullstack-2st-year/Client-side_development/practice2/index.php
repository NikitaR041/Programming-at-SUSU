<?php
require 'header.php'; // Подключаем шапку
?>
    <!-- Основа -->
    <br>
    <main>
        <?php
        require 'news-index.php'; // Второй блок
        ?>
        <br>
        <?php
        require 'news-show.php'; // Первый блок
        ?>
    </main>
<?php
require 'footer.php'; // Подключаем подвал
?>