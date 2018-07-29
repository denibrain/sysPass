<?php
/**
 * sysPass
 *
 * @author    nuxsmin
 * @link      https://syspass.org
 * @copyright 2012-2018, Rubén Domínguez nuxsmin@$syspass.org
 *
 * This file is part of sysPass.
 *
 * sysPass is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * sysPass is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with sysPass.  If not, see <http://www.gnu.org/licenses/>.
 */

namespace SP\Providers\Log;


use DI\Container;
use SP\Core\Events\Event;
use SP\Core\Events\EventReceiver;
use SP\Core\Language;
use SP\Providers\EventsTrait;
use SP\Providers\Provider;
use SplSubject;

/**
 * Class FileLogHandler
 *
 * @package SP\Providers\Log
 */
final class FileLogHandler extends Provider implements EventReceiver
{
    use EventsTrait;

    const EVENTS = [
        'database.'
    ];

    const MESSAGE_FORMAT = '%s;%s';

    /**
     * @var string
     */
    protected $events;
    /**
     * @var Language
     */
    protected $language;

    /**
     * Inicialización del observador
     */
    public function init()
    {
        // TODO: Implement init() method.
    }

    /**
     * Evento de actualización
     *
     * @param string $eventType Nombre del evento
     * @param Event  $event     Objeto del evento
     */
    public function updateEvent($eventType, Event $event)
    {
        $this->language->setAppLocales();

        if (($e = $event->getSource()) instanceof \Exception) {
            debugLog(sprintf(self::MESSAGE_FORMAT, $eventType, __($e->getMessage())));
        } elseif (($eventMessage = $event->getEventMessage()) !== null) {
            debugLog(sprintf(self::MESSAGE_FORMAT, $eventType, $eventMessage->composeText(';')));
        }

        $this->language->unsetAppLocales();
    }

    /**
     * Devuelve los eventos que implementa el observador
     *
     * @return array
     */
    public function getEvents()
    {
        return self::EVENTS;
    }

    /**
     * Devuelve los eventos que implementa el observador en formato cadena
     *
     * @return string
     */
    public function getEventsString()
    {
        return $this->events;
    }

    /**
     * Receive update from subject
     *
     * @link  http://php.net/manual/en/splobserver.update.php
     *
     * @param SplSubject $subject <p>
     *                            The <b>SplSubject</b> notifying the observer of an update.
     *                            </p>
     *
     * @return void
     * @since 5.1.0
     */
    public function update(SplSubject $subject)
    {
        // TODO: Implement update() method.
    }

    /**
     * @param Container $dic
     *
     * @throws \DI\DependencyException
     * @throws \DI\NotFoundException
     */
    protected function initialize(Container $dic)
    {
        $this->language = $dic->get(Language::class);
        $this->events = $this->parseEventsToRegex(self::EVENTS);
    }
}