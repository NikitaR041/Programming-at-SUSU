package MyFactoryEmulator;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class MyConfig {
    private final Properties props = new Properties();

    public MyConfig(String filename) throws IOException {
        try (InputStream input = getClass().getClassLoader().getResourceAsStream(filename)) {
            if (input == null) {
                throw new IOException("Файл конфигурации не найден: " + filename);
            }
            props.load(input);
        }
    }

    public int getInt(String key) {
        return Integer.parseInt(props.getProperty(key));
    }

    public String get(String key) {
        return props.getProperty(key);
    }
}
