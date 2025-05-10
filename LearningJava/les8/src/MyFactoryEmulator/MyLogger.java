package MyFactoryEmulator;
import java.io.IOException;
import java.util.logging.*;

public class MyLogger {
    public static Logger createLogger(String name) {
        Logger logger = Logger.getLogger(name);
        logger.setUseParentHandlers(false); // отключить вывод в консоль

        try {
            FileHandler fileHandler = new FileHandler("factory.log", true);
            fileHandler.setFormatter(new SimpleFormatter());
            logger.addHandler(fileHandler);
        } catch (IOException e) {
            System.err.println("Ошибка логгера: " + e.getMessage());
        }

        return logger;
    }
}
